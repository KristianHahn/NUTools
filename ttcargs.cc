#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <getopt.h>
#include <string.h>
#include <stdlib.h>
#include "ttcargs.h"

void ttc_arg_help() { 
  printf("\n");
  printf("ttctool usage: ttctool --long_option=<option value> or -short_option<option value>\n");
  printf("--------------------------------------------------------------------------------\n");
  printf("Required Options:\n");
  printf("\t--device(=)<device> or -d<device> , eg: -dapollo.c2c.vu7p\n"); 
  printf("Optional Options:\n");
  printf("\t--reset(=)<0,1,empty> or -r<0,1,empty> :  Empty argument toggles. Global reset\n"); 
  printf("\t--dump or -v : Dumps the TTC status\n"); 
  printf("\n");
}

int ttc_parse_args( int argc, char ** argv, DevStruct & dev ) {

  int opt;
  int option_index = 0;
  sprintf(dev.device,"");

static struct option long_options[] =
  {
    {"device",              required_argument, NULL, 'd'},
    {"help",                no_argument,       NULL, 'h'},
    {"mode",                required_argument, NULL, 'x'},
    {"dump",                no_argument,       NULL, 'v'},
    {NULL, 0, NULL, 0}
  };


  while(1)
    {  
      opt = getopt_long(argc, argv, ":d::x::vh",long_options, &option_index);

      if (opt == -1) 
	break; 

      switch(opt)  
        {  
	case 'd':  
	  printf("device: %s\n", optarg);  
	  if(optarg==NULL) {
	    fprintf(stderr,"Error: device must be specified with -d<device> or --device(=)<device>\n");
	    return 1;
	  }
	  sprintf(dev.device,"%s",optarg); // vu7p or ku15p
	  break;  
	case 'x':  
	  printf("mode: %s\n", optarg);  
	  if( optarg ) { 
	    dev.mode   = TTC_MODE_RST;
	    dev.ttcext = strtoul(optarg,NULL,10);
	  } else { 
	    std::cerr << "mode needs an argument ..." << std::endl;
	  }
	  break;  
	case 'v':  
	  printf("dump\n");  
	  dev.dump = 1;
	  break;  
	case 'h':  
	  ttc_arg_help();
	  dev.mode = TTC_MODE_HELP;
	  return 1;  
	case ':':  
	  printf("option needs a value, optarg is %s\n",optarg);  
	  break;  
	case '?':  
	  printf("unknown option: %c\n", optopt); 
	break;  
        }  
    }  

  if(!strlen(dev.device)) { 
    fprintf(stderr,"Error: device must be specified with -d<device> or --device(=)<device>\n");
    return 1;
  }



  return 0;
};

