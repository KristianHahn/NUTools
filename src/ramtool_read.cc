#include "uhal/uhal.hpp"
#include "uhal/log/log.hpp"
#include <vector>
#include <iomanip>
#include <stdio.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>

#include "regargs.h"

using namespace uhal;
using namespace std;

int main(int argc, char ** argv) {


  DevStruct dev;
  int ret = reg_parse_args(argc,argv,dev);
  if( ret ) return 1;
  printf("---------------------------\n");

  if(!dev.verbose)
    disableLogging();

  ConnectionManager manager ( "file://connection.xml" );
  HwInterface hw=manager.getDevice ( dev.device); 
  hw.dispatch();  


  ValVector<uint32_t> rvec;
  vector<uint32_t> wvec;

  if(dev.set) {
   printf("writing ...\n"); 
   for( int i=0; i<10; i++ ){
      wvec.push_back(dev.val+i);
      printf("pushed 0x%x\n", dev.val+i); 
  }
    hw.getNode("sender.ram.addr").write(0x0);
    hw.getNode(dev.reg).writeBlock(wvec);
    hw.dispatch();
  }
  hw.getNode("sender.ram.addr").write(0x0);
  rvec = hw.getNode(dev.reg).readBlock(10);
  hw.dispatch();

  for( int i=0; i<10; i++)
    printf("%s : 0x%x\n", dev.reg, rvec[i] );

  return 0;

}

