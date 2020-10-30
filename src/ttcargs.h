#ifndef TTCARGS
#define TTCARGS

#include <stdio.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>

//#define MGT_MODE_SET     0
#define TTC_MODE_RST    1
#define TTC_MODE_HELP   2



typedef struct { 
  char device[256];
  int  reset=-1;
  bool dump=false;
  int  mode=0;
  int  ttcext=0;
} DevStruct;


void ttc_arg_help();
int ttc_parse_args( int argc, char ** argv, DevStruct & dev );


#endif
