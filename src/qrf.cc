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


  ValVector<uint32_t> rvecA,rvecQ,rvecR;
  vector<uint32_t> wvec;


  // float values from the example
  std::vector<float> fvecA;
  fvecA.push_back(2.0);
  fvecA.push_back(-3.0);
  fvecA.push_back(4.0);
  fvecA.push_back(5.0);
  fvecA.push_back(1.0);
  fvecA.push_back(-1.0);
  fvecA.push_back(7.0);
  fvecA.push_back(4.0);
  fvecA.push_back(2.0);

  // convert to binary and write to ramA
  for( unsigned i=0; i<fvecA.size(); i++ ) { 
    unsigned * uptr = (unsigned*)&(fvecA[i]);
    for( int j=0; j<4; j++ ) { 
      unsigned val = ((*uptr)>>(j*18))&0x3ffff;
      hw.getNode("payload.ram_a.addr").write(i*4 + j);
      hw.getNode("payload.ram_a.data").write(val);
      hw.dispatch();
    }
  }



  // readback A matrix
  printf("\n readback A\n");
  printf("--------------------------------\n");
  hw.getNode("payload.ram_a.addr").write(0x0);
  rvecA = hw.getNode("payload.ram_a.data").readBlock(9*4);
  hw.dispatch();

  unsigned uvalA=0;
  for( unsigned i=0; i<rvecA.size(); i++) {
    uvalA |= rvecA[i] << (18*(i%4));
    if( (i+1)%4 == 0  ) { 
      float* fvalA = (float*)&(uvalA);
      printf( "A[%d] : 0x%x (%f)\n", i/4, uvalA, *fvalA);
      uvalA = 0;
    }
  }



  // start the HLS factorization
  ValWord< uint32_t > regval ;
  hw.getNode("payload.csr.ctrl.start").write(0x1);
  hw.dispatch();
  sleep(1);
  hw.getNode("payload.csr.ctrl.start").write(0x0);
  hw.dispatch();





  // readback Q matrix
  printf("\n readback Q\n");
  printf("--------------------------------\n");
  hw.getNode("payload.ram_q.addr").write(0x0);
  rvecQ = hw.getNode("payload.ram_q.data").readBlock(9*4);
  hw.dispatch();

  unsigned uvalQ=0;
  for( unsigned i=0; i<rvecQ.size(); i++) {
    uvalQ |= rvecQ[i] << (18*(i%4));
    if( (i+1)%4 == 0  ) { 
      float* fvalQ = (float*)&(uvalQ);
      printf( "Q[%d] : 0x%x (%f)\n", i/4, uvalQ, *fvalQ);
      uvalQ = 0;
    }
  }



  // readback R matrix
  printf("\n readback R\n");
  printf("--------------------------------\n");
  hw.getNode("payload.ram_r.addr").write(0x0);
  rvecR = hw.getNode("payload.ram_r.data").readBlock(9*4);
  hw.dispatch();

  unsigned uvalR=0;
  for( unsigned i=0; i<rvecR.size(); i++) {
    uvalR |= rvecR[i] << (18*(i%4));
    if( (i+1)%4 == 0  ) { 
      float* fvalR = (float*)&(uvalR);
      printf( "R[%d] : 0x%x (%f)\n", i/4, uvalR, *fvalR);
      uvalR = 0;
    }
  }

  return 0;

}

