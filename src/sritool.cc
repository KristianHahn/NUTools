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
    uint32_t ctrlwrd = 0x80000000;
    if( dev.pause > 0)
      ctrlwrd |= dev.pause;
    else ctrlwrd |= 0x3ff;
    hw.getNode("payload.csr.ctrl").write(ctrlwrd);
    hw.dispatch();
    sleep(1);
    // turn off bypass ram
    hw.getNode("sender.csr.ctrl0").write(0x0);
    hw.dispatch();
    sleep(1);
    // turn off cdfifo ram
    hw.getNode("sender.channel1.cdfifo.csr.ctrl").write(0x0);
    hw.getNode("sender.channel0.cdfifo.csr.ctrl").write(0x0);
    hw.dispatch();
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
    hw.getNode("sender.csr.ctrl2").write(0x40000000);
    hw.dispatch();

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
    hw.getNode("sender.csr.ctrl2").write(0x40000000);
    hw.dispatch();

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
  
    //load c/d, ttc, let seq go
    hw.getNode("sender.csr.ctrl2").write(0x00000000);
    hw.dispatch();

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

  // set capture ctrl fifo to ram & readout
  if( dev.mode == SRI_MODE_PLAY_CDFIFO_OLD ) { 
    vector<uint64_t> cdram;
    vector<uint32_t> cdram_32;
    // split off ttc later ...
    vector<uint64_t> ttcram0,ttcram1;
    vector<uint32_t> ttcram0_32, ttcram1_32;

    // hold seq in rst till filled
    hw.getNode("sender.csr.ctrl2").write(0x40000000);
    hw.dispatch();

    //
    // tmp, do ttc here ...
    //


    //  if(dev.set) {
    printf("writing ...\n"); 
    //   for( int i=0; i<10; i++ ){

    ttcram0.push_back(0xcccbeeff00d);
    ttcram1.push_back(0x1);
    ttcram0.push_back(0xcccd00df00d);
    ttcram1.push_back(0x2);
    ttcram0.push_back(0xeeebabef00d);
    ttcram1.push_back(0x3);
    ttcram0.push_back(0xddddeadf00d);
    ttcram1.push_back(0x4);

    for( int i=0; i<ttcram0.size(); i++ ) { 
      unsigned long long tmp = ttcram0[i];
      for( int j=0; j<4; j++ ) { 
	unsigned shifted = (tmp>>(j*18)) & 0x3ffff;
	ttcram0_32.push_back(shifted);
      }
    }
    for( int i=0; i<ttcram0_32.size(); i++ ) { 
      std::cout << "ttcram0:: " << std::dec << i << "\t"
		<< std::hex << ttcram0_32[i] << std::endl;
    }

    for( int i=0; i<ttcram1.size(); i++ ) { 
      unsigned long long tmp = ttcram1[i];
      for( int j=0; j<4; j++ ) { 
	unsigned shifted = (tmp>>(j*18)) & 0x3ffff;
	ttcram1_32.push_back(shifted);
      }
    }
    for( int i=0; i<ttcram1_32.size(); i++ ) { 
      std::cout << "ttcram1:: " << std::dec << i << "\t"
		<< std::hex << ttcram1_32[i] << std::endl;
    }

    hw.getNode("sender.channel0.ttcfifo.ram0.addr").write(0x0);
    hw.getNode("sender.channel0.ttcfifo.ram1.addr").write(0x0);
    hw.getNode("sender.channel1.ttcfifo.ram0.addr").write(0x0);
    hw.getNode("sender.channel1.ttcfifo.ram1.addr").write(0x0);
    hw.dispatch();
    hw.getNode("sender.channel0.ttcfifo.ram0.data").writeBlock(ttcram0_32);
    hw.getNode("sender.channel0.ttcfifo.ram1.data").writeBlock(ttcram1_32);
    hw.getNode("sender.channel1.ttcfifo.ram0.data").writeBlock(ttcram0_32);
    hw.getNode("sender.channel1.ttcfifo.ram1.data").writeBlock(ttcram1_32);
    hw.dispatch();



    // 1st packet data
    cdram.clear();
    cdram.push_back(0xfeedfacedeadbeef);
    cdram.push_back(0x1111111111111111);
    cdram.push_back(0x2222222222222222);
    cdram.push_back(0x3333333333333333);
    cdram.push_back(0x4444444444444444);
    cdram.push_back(0x5555555555555555);
    cdram.push_back(0x6666666666666666);
    cdram.push_back(0xfefecdcdefefdcdc);
    for( int i=0; i<cdram.size(); i++ ) { 
      unsigned long long tmp = cdram[i];
      for( int j=0; j<4; j++ ) { 
	unsigned shifted = (tmp>>(j*18)) & 0x3ffff;
	if( i == 0 && j==3)
	  shifted |= 0x1800; //110 start+valid
	else if (i == cdram.size()-1 && j==3) 
	  shifted |= 0x0c00; //011 valid+end
	else if( j == 3)
	  shifted |= 0x0800; //010 valid
	//       std::cout << "0 shifted : " <<std:: hex << shifted << std::endl;
	cdram_32.push_back(shifted);
      }
    }
    cdram_32.push_back(0);
    cdram_32.push_back(0);
    cdram_32.push_back(0);
    cdram_32.push_back(0);

    // 2nd packet data
    cdram.clear();
    cdram.push_back(0x1010202030304040);
    for( int i=0; i<cdram.size(); i++ ) { 
      unsigned long long tmp = cdram[i];
      for( int j=0; j<4; j++ ) { 
	unsigned shifted = (tmp>>(j*18)) & 0x3ffff;
	if( j ==3 ) 
	  shifted |= 0x1c00; //111 start+valid+end
	cdram_32.push_back(shifted);
      }
    }
    cdram_32.push_back(0);
    cdram_32.push_back(0);
    cdram_32.push_back(0);
    cdram_32.push_back(0);

    // 3rd packet data
    cdram.clear();
    cdram.push_back(0xEEEEEEEEEEEEEEEE);
    for( int i=0; i<cdram.size(); i++ ) { 
      unsigned long long tmp = cdram[i];
      for( int j=0; j<4; j++ ) { 
	unsigned shifted = (tmp>>(j*18)) & 0x3ffff;
	if( j == 3) 
	  shifted |= 0x1400; //101 start+end (invalid)
	cdram_32.push_back(shifted);
      }
    }
    cdram_32.push_back(0);
    cdram_32.push_back(0);
    cdram_32.push_back(0);
    cdram_32.push_back(0);

    // 4th packet data
    cdram.clear();
    cdram.push_back(0xe0ffe0ffe0ffe0ff);
    cdram.push_back(0xaaaaaaaaaaaaaaaa);
    cdram.push_back(0xbbbbbbbbbbbbbbbb);
    cdram.push_back(0xcccccccccccccccc);
    cdram.push_back(0xdddddddddddddddd);
    for( int i=0; i<cdram.size(); i++ ) { 
      unsigned long long tmp = cdram[i];
      for( int j=0; j<4; j++ ) { 
	unsigned shifted = (tmp>>(j*18)) & 0x3ffff;
	if( i == 0 && j == 3 )
	  shifted |= 0x1800; //110 start+valid
	else if (i == cdram.size()-1 && j==3) 
	  shifted |= 0x0c00; //010 valid
	else if( j == 3)
	  shifted |= 0x0800; //011 valid+end
	cdram_32.push_back(shifted);
      }
    }
    cdram_32.push_back(0);
    cdram_32.push_back(0);
    cdram_32.push_back(0);
    cdram_32.push_back(0);


    std::cout << "cdram:: " << std::endl;
    for( int i=0; i<cdram_32.size(); i++ ) {    
      std::cout << "i: " << std::dec << i << "\t"
		<< "d: " << std::hex << cdram_32[i]
		<< std::endl;
    }

    // reset ram addr
    hw.getNode("sender.channel0.cdfifo.ram.addr").write(0x0);
    hw.getNode("sender.channel1.cdfifo.ram.addr").write(0x0);
    hw.dispatch();
    // write packet data to ram
    hw.getNode("sender.channel0.cdfifo.ram.data").writeBlock(cdram_32);
    hw.dispatch();
    hw.getNode("sender.channel1.cdfifo.ram.data").writeBlock(cdram_32);
    hw.dispatch();

    //load c/d, ttc, let seq go
    hw.getNode("sender.csr.ctrl2").write(0x00000000);
    hw.dispatch();



    hw.getNode("sender.channel0.ttcfifo.csr.ctrl").write(0x60000000 + ttcram0_32.size()/4);
    hw.getNode("sender.channel1.ttcfifo.csr.ctrl").write(0x60000000 + ttcram0_32.size()/4);


    std::cout << "ttcram0_32.size()/4: "  << (ttcram0_32.size())/4 << std::endl;
    hw.dispatch();

    uint32_t ctrlwrd = 0x60000000;
    if( dev.pause > 0)
      ctrlwrd |= dev.pause;
    else ctrlwrd |= 0x3ff;
    ctrlwrd |= cdram_32.size()/4;
    hw.getNode("sender.channel1.cdfifo.csr.ctrl").write(ctrlwrd);
    hw.getNode("sender.channel0.cdfifo.csr.ctrl").write(ctrlwrd);
    hw.dispatch();
  }

  
  
  return 0;

}

