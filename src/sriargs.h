#ifndef MGTARGS
#define MGTARGS

#include <stdio.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>
#include <string>
#include "uhal/uhal.hpp"

#define SRI_MODE_PAYLOAD          0

#define SRI_MODE_LOAD_CDFIFO      1
#define SRI_MODE_LOAD_TTCFIFO     2
#define SRI_MODE_PLAY_CDFIFO      3

#define SRI_MODE_CDFIFO_CAPTURE   4

#define SRI_MODE_LOAD_BYPASS      5
#define SRI_MODE_BYPASS_FORMAT    6

#define SRI_MODE_PARSE_CAPTURE    7

#define SRI_MODE_PLAY_CDFIFO_OLD  8

#define SRI_MODE_HELP 999

using namespace std;

typedef struct { 
  char device[256];
  int  channel=-1;
  int  pause=-1;
  /* int  channel=0xf; */
  /* int  loopback=-1; */
  /* int  tx_polarity=-1; */
  /* int  rx_polarity=-1; */
  /* int  rx_lpm=-1; */
  int  reset=-1;
  bool dump=false;
  /* int  tx_usrrst=-1; */
  /* int  rx_usrrst=-1; */
  /* int  reset_crc_counters=-1; */
  int  mode=0;
  /* int  ttcext=0; */
  /* int  total_delta=0; */
  bool set=false;
  bool verbose=false;
  std::string filename;
  /* unsigned prefix=0x0; */
} DevStruct;


void sri_arg_help();
int sri_parse_args( int argc, char ** argv, DevStruct & dev );
int load_bypass_data(uhal::HwInterface & hw, const char * fname, int channel);
int load_cd_fifo(uhal::HwInterface & hw, const char * fname, int channel);
int load_ttc_fifo(uhal::HwInterface & hw, const char * fname, int channel);

#endif
