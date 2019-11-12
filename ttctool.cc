#include "uhal/uhal.hpp"
#include "uhal/log/log.hpp"
#include <vector>
#include <iomanip>
#include <stdio.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>

#include "ttcargs.h"
#include "ttcroutines.h"

using namespace uhal;
using namespace std;

int main(int argc, char ** argv) {


  DevStruct dev;
  int ret = ttc_parse_args(argc,argv,dev);
  if( ret ) return 1;
  printf("----------------------------------\n");

  disableLogging();

  ConnectionManager manager ( "file://connection.xml" );
  HwInterface hw=manager.getDevice ( dev.device );

  ValWord< uint32_t > valv  =   hw.getNode ( "info.versions" ).read();
  hw.dispatch();
  std::cout << std::endl;
  std::cout << "version: " << std::hex << valv << std::endl;
  std::cout << std::endl;  


  if( dev.mode == TTC_MODE_HELP ) {     
    ttc_arg_help();
    return 1;
  }

  if( dev.mode == TTC_MODE_RST)         ttc_reset(hw,dev);
  if( dev.dump )                        ttc_dump(hw,dev);	    


}

