#include <stdio.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>
#include <stdlib.h>
#include "regargs.h"

void reg_arg_help() { 
  printf("\n");
  printf("regtool usage: regtool [--long_option=<value> or -short_option<value>] [regval]\n");
  printf("--------------------------------------------------------------------------------\n");
  printf("Required Options:\n");
  printf("\t--device(=)<device> or -d<device> , eg: -dapollo.c2c.vu7p\n"); 
  printf("\t--reg(=)<regname> or -r<regname> , eg: -rinfo.version\n"); 
  printf("Optional Options:\n");
  printf("\tregval : if given, regname is set to this (hex) value, otherwise the value in regname is returned\n"); 
  printf("\n");
}

int reg_parse_args( int argc, char ** argv, DevStruct & dev ) {

  int opt;
  int option_index = 0;
  sprintf(dev.device,"");

static struct option long_options[] =
  {
    {"help",                no_argument,       NULL, 'h'},
    {"device",              required_argument, NULL, 'd'},
    {"reg",                 required_argument, NULL, 'r'},
    {"verbose",             no_argument,       NULL, 'v'},
    {NULL, 0, NULL, 0}
  };


  while(1)
    {  
      opt = getopt_long(argc, argv, ":d::r::hv",long_options, &option_index);

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
	case 'r':  
	  printf("reg: %s\n", optarg);  
	  if(optarg==NULL) {
	    fprintf(stderr,"Error: reg must be specified with -r<regname> or --reg(=)<regname>\n");
	    return 1;
	  }
	  sprintf(dev.reg,"%s", optarg);
	  break;  
	case 'h':  
	  reg_arg_help();
	  return 1;  
	case 'v':  
	  dev.verbose = true;
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

  if(!strlen(dev.reg)) {
    fprintf(stderr,"Error: register name must be specified with -r<name> or --reg(=)<name>\n");
    return 1;
  }


  // optind is for the extra arguments 
  // which are not parsed 
  if( optind < argc ) { 
    dev.val = strtoul(argv[optind],NULL,16);
    dev.set = true;
  }

  return 0;
};

