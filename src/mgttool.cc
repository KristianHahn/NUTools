#include "uhal/uhal.hpp"
#include "uhal/log/log.hpp"
#include <vector>
#include <iomanip>
#include <stdio.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>

#include "mgtargs.h"
#include "mgtroutines.h"

using namespace uhal;
using namespace std;

int main(int argc, char ** argv) {

  const char* nu_xml = getenv("NU_TOOLS_XML");
  if (nu_xml == NULL) {
    printf("Please set NU_TOOLS_XML\n");
    return 1;
  }

  DevStruct dev;
  int ret = mgt_parse_args(argc,argv,dev);
  if( ret ) return 1;
  printf("----------------------------------\n");

  disableLogging();

  std::string connstr = nu_xml + std::string("/connection.xml");
  ConnectionManager manager ( connstr.c_str() );
  HwInterface hw=manager.getDevice ( dev.device );

  ValWord< uint32_t > valv  =   hw.getNode ( "info.versions" ).read();
  hw.dispatch();
  std::cout << std::endl;
  std::cout << "version: " << std::hex << valv << std::endl;
  std::cout << std::endl;  


  // set the quad first, always 
  hw.getNode ( "datapath.ctrl.quad_sel" ).write(dev.quad_id);
  hw.dispatch();

  if( dev.mode == MGT_MODE_HELP ) {     
    mgt_arg_help();
    return 1;
  }
  if( dev.mode == MGT_MODE_SET ) { 
    //
    if( dev.loopback >= 0 )               mgt_set_loopback(hw,dev);
    if( dev.tx_polarity >= 0 )            mgt_tx_polarity(hw,dev);
    if( dev.rx_polarity >= 0 )            mgt_rx_polarity(hw,dev);
    if( dev.rx_lpm >= 0 )                 mgt_rx_lpm(hw,dev);
    //
    if( dev.reset >= 0)                   mgt_global_reset(hw,dev);
    if( dev.tx_usrrst >= 0)               mgt_tx_usr_reset(hw,dev); 
    if( dev.rx_usrrst >= 0)               mgt_rx_usr_reset(hw,dev); 
    if( dev.reset_crc_counters >= 0)      mgt_reset_crc_counters(hw,dev); 
    if( dev.dump )                        mgt_dump(hw,dev);	    
  } 
  else if(dev.mode == MGT_MODE_PLAY)      { 
    if(dev.bufftype < 0) dev.bufftype = kTX;
    if(!(dev.filename.empty()))
       mgt_play_file(hw,dev);
    else
      mgt_play_pattern(hw,dev);
  }
  else if(dev.mode == MGT_MODE_CAPTURE)   {
    if(dev.bufftype < 0) dev.bufftype = kRX;
    mgt_capture(hw,dev); 
  }
  else if(dev.mode == MGT_MODE_ALIGN)     mgt_align(hw,dev); 
  else ;

}

