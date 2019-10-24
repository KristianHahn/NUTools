#ifndef REGARGS
#define REGARGS

#include <stdio.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>


typedef struct { 
  char device[256];
  char reg[512];
  bool set=false;
  bool verbose=false;
  unsigned val;
} DevStruct;


void reg_arg_help();
int reg_parse_args( int argc, char ** argv, DevStruct & dev );


#endif
