#include "uhal/uhal.hpp"
#include "uhal/log/log.hpp"
#include <vector>
#include <iomanip>
#include <stdio.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>

#include "sriargs.h"

using namespace uhal;
using namespace std;

int main(int argc, char ** argv) {

  const char* nu_xml = getenv("NU_TOOLS_XML");
  if (nu_xml == NULL) {
    printf("Please set NU_TOOLS_XML\n");
    return 1;
  }

  DevStruct dev;
  int ret = sri_parse_args(argc,argv,dev);
  if( ret ) return 1;
  printf("---------------------------\n");


  if(!dev.verbose)
    disableLogging();

  std::string connstr = nu_xml + std::string("/connection.xml");
  ConnectionManager manager ( connstr.c_str() );
  HwInterface hw=manager.getDevice ( dev.device); 
  hw.dispatch();  



  ValVector<uint32_t> rvec;
  vector<uint32_t> wvec;


  // payload generation with pause, working
  if(dev.mode == SRI_MODE_PAYLOAD) { 
    // turn off bypass ram
    hw.getNode("sender.csr.ctrl0.use_bypass_ram").write(0x0);
    hw.dispatch();
    sleep(1);
    // turn off cdfifo ram
    hw.getNode("sender.channel1.cdfifo.csr.ctrl").write(0x0);
    hw.getNode("sender.channel0.cdfifo.csr.ctrl").write(0x0);
    hw.dispatch();

    uint32_t ctrlwrd = 0x80000000;
    if( dev.pause > 0)
      ctrlwrd |= dev.pause;
    else ctrlwrd |= 0x3ff;
    hw.getNode("payload.csr.ctrl").write(ctrlwrd);
    hw.dispatch();
    sleep(1);

  }
  
  // set capture ctrl fifo to ram & readout, working
  if( dev.mode == SRI_MODE_CDFIFO_CAPTURE ) { 
    hw.getNode("sender.channel0.cdfifo.csr.ctrl.capture_to_ram").write(1);
    hw.dispatch();
    sleep(1);
    hw.getNode("sender.channel0.cdfifo.ram.addr").write(0);
    hw.dispatch();
    rvec = hw.getNode("sender.channel0.cdfifo.ram.data").readBlock(1024);//ram.data
    hw.dispatch();
    
    printf("vec size: %d\n", rvec.size() );
    for( int i=0; i<rvec.size(); i++)
      //      printf("%s : 0x%x\n", dev.reg, rvec[i] );
      printf("%d : 0x%x\n", i, rvec[i] );
  }

  
  // set capture ctrl fifo to ram & readout
  if( dev.mode == SRI_MODE_LOAD_TTCFIFO ) { 

    // hold seq in rst till filled
    //hw.getNode("sender.csr.ctrl2").write(0x40000000);
    //hw.dispatch();

    //load
    printf("writing ...\n"); 
    load_ttc_fifo( hw,dev.filename.c_str(),0);
    load_ttc_fifo( hw,dev.filename.c_str(),1);
    hw.dispatch();
    sleep(1);

    }

  // set capture ctrl fifo to ram & readout
  if( dev.mode == SRI_MODE_LOAD_CDFIFO ) { 

    // hold seq in rst till filled
    //hw.getNode("sender.csr.ctrl2").write(0x40000000);
    //hw.dispatch();

    //load
    printf("writing ...\n"); 
    int nwords = load_cd_fifo( hw,dev.filename.c_str(),dev.channel);
    hw.dispatch();
    sleep(1);

    char strA[256];
    sprintf(strA,"sender.channel%d.cdfifo.csr.ctrl", dev.channel);
    hw.getNode(strA).write(nwords);
    hw.dispatch();
    sleep(1);
    }

  if( dev.mode == SRI_MODE_PLAY_CDFIFO ) { 
  
    // turn off bypass, payload
    hw.getNode("sender.csr.ctrl0.use_bypass_ram").write(0x0);
    hw.getNode("payload.csr.ctrl").write(0x0);
    hw.dispatch();

    //load c/d, ttc, let seq go
    //hw.getNode("sender.csr.ctrl2").write(0x00000000);
    //    hw.dispatch();

    if( dev.pause > 0){
      hw.getNode("sender.channel0.cdfifo.csr.ctrl.ram_read_pause").write(dev.pause);
      hw.getNode("sender.channel1.cdfifo.csr.ctrl.ram_read_pause").write(dev.pause);
    } else {
      hw.getNode("sender.channel0.cdfifo.csr.ctrl.ram_read_pause").write(0x3ff);
      hw.getNode("sender.channel1.cdfifo.csr.ctrl.ram_read_pause").write(0x3ff);
    }

    hw.dispatch();
    sleep(1);


    
    hw.getNode("sender.channel1.cdfifo.csr.ctrl.ram_loaded").write(1);
    hw.getNode("sender.channel1.cdfifo.csr.ctrl.load_from_ram").write(1);
    hw.getNode("sender.channel0.cdfifo.csr.ctrl.ram_loaded").write(1);
    hw.getNode("sender.channel0.cdfifo.csr.ctrl.load_from_ram").write(1);
    hw.dispatch();
  }

  
  
  // set capture ctrl fifo to ram & readout
  if( dev.mode == SRI_MODE_LOAD_BYPASS ) { 
    //  if(dev.set) {
    printf("writing ...\n"); 
    int nwords = load_bypass_data( hw,dev.filename.c_str(),dev.channel);
    hw.getNode("sender.csr.ctrl0.bypass_ram_nwords").write(nwords);
    hw.dispatch();
    sleep(1);
  }
  

  if( dev.mode == SRI_MODE_BYPASS_FORMAT ) { 

    //  if(dev.set) {
    // printf("writing ...\n"); 
    // int nwords = load_bypass_data( hw,"/home/cms/NUTools/bypass0.dat",0);
    // load_bypass_data( hw,"/home/cms/NUTools/bypass1.dat", 1);

    // check nwords is non-zero

    // send the ram data
    unsigned ctrlwrd = 1;
    hw.getNode("sender.csr.ctrl0.use_bypass_ram").write(ctrlwrd);
    hw.dispatch();

    sleep(1);
  }


  if( dev.mode == SRI_MODE_PARSE_CAPTURE ) { 
    FILE * f = fopen(dev.filename.c_str(),"r");
    char *str = (char *)malloc(256*sizeof(char));
    size_t len;

    int count=0;
    uint64_t val=0;

    bool found_nonzero = false;
    while( !feof(f) ) { 
      //    str = (char *)malloc(256*sizeof(char));
      int nlen = getline( &str, &len, f );
      if( feof(f) or !nlen ) break;
      char * ptr = strtok( str, ":");
      if( ptr == NULL ) continue;
    
      ptr = strtok(NULL,":");
    
      uint64_t tmpval = strtoul(ptr,NULL,16);
      if( tmpval != 0 ) found_nonzero = true;
      if( !found_nonzero ) continue; //skipping all leading zeros ...
    
      std::cout << std::hex << tmpval << std::endl;
      if( count < 3 )  {
	val |= ((tmpval&0x3ffff)<<18*count);
	count++;
      } else { 
	val |= ((tmpval&0x3ff)<<18*count);
	unsigned ctrl = (tmpval&0x1c00)>>10;
	std::cout << "--->" << std::hex << ctrl << ":" << val << std::endl;      
	count = 0;
	val = 0;
      }
    }
    free(str);
  }



  
  
  return 0;

}

