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

  const char* nu_xml = getenv("NU_TOOLS_XML");
  if (nu_xml == NULL) {
    printf("Please set NU_TOOLS_XML\n");
    return 1;
  }

  DevStruct dev;
  int ret = reg_parse_args(argc,argv,dev);
  if( ret ) return 1;
  printf("---------------------------\n");

  if(!dev.verbose)
    disableLogging();

  std::string connstr = nu_xml + std::string("/connection.xml");
  ConnectionManager manager ( connstr.c_str() );
  HwInterface hw=manager.getDevice ( dev.device ); 
  hw.dispatch();  

  if(dev.set) {
    hw.getNode(dev.reg).write(dev.val);
    hw.dispatch();
  }
  ValWord< uint32_t > regval = hw.getNode(dev.reg).read();
  hw.dispatch();

  printf("%s : 0x%x\n", dev.reg, regval.value() );

  return 0;

}

