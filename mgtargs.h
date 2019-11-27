#ifndef MGTARGS
#define MGTARGS

#include <stdio.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>
#include <string>

#define MGT_MODE_SET     0
#define MGT_MODE_PLAY    1
#define MGT_MODE_CAPTURE 2
#define MGT_MODE_HELP    3
#define MGT_MODE_ALIGN   4
#define MGT_RESET_TOGGLE 999

using namespace std;

typedef struct { 
  char device[256];
  int  quad_id=-1;
  int  bufftype=-1;
  int  channel=0xf;
  int  loopback=-1;
  int  tx_polarity=-1;
  int  rx_polarity=-1;
  int  rx_lpm=-1;
  int  reset=-1;
  bool dump=false;
  int  tx_usrrst=-1;
  int  rx_usrrst=-1;
  int  reset_crc_counters=-1;
  int  mode=0;
  int  ttcext=0;
  int  total_delta=0;
  string filename;
  unsigned prefix=0x0;
} DevStruct;


void mgt_arg_help();
int mgt_parse_args( int argc, char ** argv, DevStruct & dev );


#endif
