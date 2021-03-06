#include "uhal/uhal.hpp"
#include "uhal/log/log.hpp"
#include <vector>
#include <iomanip>
#include <stdio.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>

#include <bits/stdc++.h> 
//#include <iostream>
//include <string>
//#include <regex>
//#include <iterator>

#include "regargs.h"


#include <boost/xpressive/xpressive.hpp>

using namespace boost::xpressive;

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
  HwInterface hw=manager.getDevice ( dev.device); 
  hw.dispatch();  


  ValVector<uint32_t> rvec;
  vector<uint32_t> wvec;

  string str = dev.reg;
  sregex re = as_xpr("data");
  string astr = regex_replace(str,re,string("addr"));

  cout << "str: " << str << endl;
  cout << "astr: " << astr.c_str() << endl;

  if(dev.set) {
   printf("writing ...\n"); 
   for( unsigned i=0; i<28; i++ ){
      wvec.push_back(dev.val+i);
      printf("pushed 0x%x\n", dev.val+i); 
  }
    hw.getNode(astr.c_str()).write(0x0);
    hw.getNode(dev.reg).writeBlock(wvec);
    hw.dispatch();
  }
  hw.getNode(astr.c_str()).write(0x0);
  rvec = hw.getNode(dev.reg).readBlock(256);
  hw.dispatch();

  for( unsigned i=0; i<rvec.size(); i++)
    printf("%s : 0x%x\n", dev.reg, rvec[i] );

  return 0;

}

