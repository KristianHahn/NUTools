#include <stdio.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>
#include <stdlib.h>
#include <vector>
#include <iostream>
#include <iomanip>
#include "sriargs.h"


void sri_arg_help() { 
  printf("\n");
  printf("sritool usage: sritool --long_option=<option value> or -short_option<option value>\n");
  printf("--------------------------------------------------------------------------------\n");
  printf("Required Options:\n");
  printf("\t--device(=)<device> or -d<device> , eg: -dapollo.c2c.vu7p\n"); 
  printf("\t--channel(=)<channel> or -c<channel> , eg: -c0\n"); 
  printf("Optional Options:\n");
  printf("\t--reset(=)<0,1,empty> or -r<0,1,empty> :  Empty argument toggles. Global reset\n"); 
  printf("\t--txusrrst(=)<0,1,empty>. Empty argument toggles : Defaults to all channels\n"); 
  printf("\t--rxusrrst(=)<0,1,empty>. Empty argument toggles : Defaults to all channels\n"); 
  printf("\t--reset_crc_counters(=)<0,1,empty> : Empty argument toggles. Defaults to all channels\n"); 
  printf("\t--loopback(=)<mode> or -l<mode> :  Defaults to all channels\n"); 
  printf("\t--txpolarity(=)<mode> :  Defaults to all channels\n"); 
  printf("\t--rxpolarity(=)<mode> :  Defaults to all channels\n"); 
  printf("\t--rxlpm(=)<mode> :  Defaults to all channels\n"); 
  printf("\t--channel(=)<value> or -c<value> : A channel ID (0-3) for play/capture, a bitmask (0x1-0xf) otherwise \n"); 
  printf("\t--bufftype(=)<value> or -b<value> : Buffer type for play/capture, 'tx' or 'rx' \n"); 
  printf("\t--play(=)<prefix> or -p<prefix>: Requires channel spec.  Prefix added to MS nibble of each 16b word \n"); 
  printf("\t\t--file(=)<filename> or -f<filename>: optional filename for play\n"); 
  printf("\t--capture : Requires channel specification\n"); 
  printf("\t--dump or -v : Dumps the MGT status\n"); 
  printf("\n");
}

int sri_parse_args( int argc, char ** argv, DevStruct & dev ) {

  int opt;
  int option_index = 0;
  sprintf(dev.device,"");

static struct option long_options[] =
  {
    {"device",              required_argument, NULL, 'd'},
    {"channel" ,            required_argument, NULL, 'c'},
    {"pause",               required_argument, NULL, 'p'},
    {"file",                required_argument, NULL, 'f'},
    {"payload",             no_argument,       NULL, 0},
    {"capture",             no_argument,       NULL, 0},
    {"parse",               no_argument,       NULL, 0},
    {"load_ttcfifo",        no_argument,       NULL, 0},
    {"load_cdfifo",         no_argument,       NULL, 0},
    {"play_cdfifo",         no_argument,       NULL, 0},
    {"play_cdfifo_old",         no_argument,       NULL, 0},
    {"load_bypass",         no_argument,       NULL, 0},
    {"bypass",              no_argument,       NULL, 0},
    {"help",                no_argument,       NULL, 'h'},
    {NULL, 0, NULL, 0}
  };


  while(1)
    {  
      opt = getopt_long(argc, argv, ":d::c::p::f::h0::",long_options, &option_index);

      if (opt == -1) 
	break; 

      switch(opt)  
        {  
	case 0: 
	  printf("option -->%s\n", long_options[option_index].name); 
	  if(!strcmp(long_options[option_index].name,"parse") ) {
	    printf("parse capture\n");
	    dev.mode=SRI_MODE_PARSE_CAPTURE;
	    // if(optarg) dev.prefix = (strtoul(optarg,NULL,16))<<12U;
	    // else dev.prefix=0;
	    // printf("\tprefix value: 0x%x\n",dev.prefix);
	  }
	  if(!strcmp(long_options[option_index].name,"payload") ) {
	    printf("payload\n");
	    dev.mode=SRI_MODE_PAYLOAD;
	    // if(optarg) dev.prefix = (strtoul(optarg,NULL,16))<<12U;
	    // else dev.prefix=0;
	    // printf("\tprefix value: 0x%x\n",dev.prefix);
	  }
	  if(!strcmp(long_options[option_index].name,"load_cdfifo") ) {
	    printf("load ctrl fifo\n");
	    dev.mode=SRI_MODE_LOAD_CDFIFO;
	    // if(optarg) dev.prefix = (strtoul(optarg,NULL,16))<<12U;
	    // else dev.prefix=0;
	    // printf("\tprefix value: 0x%x\n",dev.prefix);
	  }
	  if(!strcmp(long_options[option_index].name,"load_ttcfifo") ) {
	    printf("load ttc fifo\n");
	    dev.mode=SRI_MODE_LOAD_TTCFIFO;
	    // if(optarg) dev.prefix = (strtoul(optarg,NULL,16))<<12U;
	    // else dev.prefix=0;
	    // printf("\tprefix value: 0x%x\n",dev.prefix);
	  }
	  if(!strcmp(long_options[option_index].name,"play_cdfifo") ) {
	    printf("playing cdfifo\n");
	    dev.mode=SRI_MODE_PLAY_CDFIFO;
	    // if(optarg) dev.prefix = (strtoul(optarg,NULL,16))<<12U;
	    // else dev.prefix=0;
	    // printf("\tprefix value: 0x%x\n",dev.prefix);
	  }
	  if(!strcmp(long_options[option_index].name,"play_cdfifo_old") ) {
	    printf("playing cdfifo\n");
	    dev.mode=SRI_MODE_PLAY_CDFIFO_OLD;
	    // if(optarg) dev.prefix = (strtoul(optarg,NULL,16))<<12U;
	    // else dev.prefix=0;
	    // printf("\tprefix value: 0x%x\n",dev.prefix);
	  }
	  if(!strcmp(long_options[option_index].name,"capture") ) {
	    printf("capture ctrl fifo\n");
	    dev.mode=SRI_MODE_CDFIFO_CAPTURE;
	    // if(optarg) dev.prefix = (strtoul(optarg,NULL,16))<<12U;
	    // else dev.prefix=0;
	    // printf("\tprefix value: 0x%x\n",dev.prefix);
	  }
	  if(!strcmp(long_options[option_index].name,"load_bypass") ) {
	    printf("load bypass formatting\n");
	    dev.mode=SRI_MODE_LOAD_BYPASS;
	    // if(optarg) dev.prefix = (strtoul(optarg,NULL,16))<<12U;
	    // else dev.prefix=0;
	    // printf("\tprefix value: 0x%x\n",dev.prefix);
	  }
	  if(!strcmp(long_options[option_index].name,"bypass") ) {
	    printf("load bypass formatting\n");
	    dev.mode=SRI_MODE_BYPASS_FORMAT;
	    // if(optarg) dev.prefix = (strtoul(optarg,NULL,16))<<12U;
	    // else dev.prefix=0;
	    // printf("\tprefix value: 0x%x\n",dev.prefix);
	  }
	  break;

	case 'd':  
	  printf("device: %s\n", optarg);  
	  if(optarg==NULL) {
	    fprintf(stderr,"Error: device must be specified with -d<device> or --device(=)<device>\n");
	    return 1;
	  }
	  sprintf(dev.device,"%s",optarg); // vu7p or ku15p
	  break;  
	case 'c':  
	  printf("channel: %s\n", optarg);  
	  if(optarg==NULL) {
	    fprintf(stderr,"Error: channel mask must be specified with -c<mask> or --channel(=)<mask>\n");
	    return 1;
	  }
	  dev.channel = strtoul(optarg,NULL,16);
	  break;  
	case 'p':  
	  printf("pause: %s\n", optarg);  
	  if(optarg==NULL) {
	    fprintf(stderr,"Error: pause must be specified with -p<mask> or --pause(=)<mask>\n");
	    return 1;
	  }
	  dev.pause = strtol(optarg,NULL,16);
	  break;  
	case 'f':  
	  printf("file: %s\n", optarg);  
	  if(optarg==NULL) {
	    fprintf(stderr,"Error: filename must be specified with -f<filename> or --file(=)<filename>\n");
	    return 1;
	  }
	  dev.filename = std::string(optarg);
	  break;  
	case 'h':  
	  sri_arg_help();
	  dev.mode = SRI_MODE_HELP;
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


   // if( dev.mode == SRI_MODE_BYPASS_FORMAT && dev.file == NULL) {
   //      fprintf(stderr,"Specify data file for bypass mode with -f or --file\n");  
   // 	return 1;
   // }

  // if( dev.mode == MGT_MODE_SET && (dev.channel <= 0 || dev.channel > 15 )) {
  //   fprintf(stderr,"Valid values for --channel in set play/capture modes are 0x1-0xf\n");  
  //   return 1;
  // }


  return 0;
};

int 
load_bypass_data(uhal::HwInterface & hw, const char * fname, int channel)
{ 
  FILE * f = fopen(fname,"r"); 
  size_t len; 

  char *str = (char *)malloc(1024*sizeof(char)); 
 
  unsigned valA;
  uint64_t valB,valC;
  std::vector<uint32_t> ram0,ram1;
  int count=0;

  // pad
  for( int i=0; i<4; i++ ) {
      ram0.push_back(0);
      ram0.push_back(0);
      ram0.push_back(0);
      ram0.push_back(0);
      ram1.push_back(0);
      ram1.push_back(0);
      ram1.push_back(0);
      ram1.push_back(0);
    }

  while( !feof(f) ) {  

    int nlen = getline( &str, &len, f ); 
    if( !strncmp(str,"#",1) or !strncmp(str,"\n",1)  ) { 
      continue; 
    } 
    sscanf(str,"%x %llx %llx", &valA, &valB, &valC  ); 
    std::cout  << std::dec << count << " "
	       << std::hex << std::setfill('0') 
	       << std::setw(1)  << valA << " " 
	       << std::setw(16) << valB << " " 
	       << std::setw(16) << valC << " " 
	       << std::endl; 
    count++;

    unsigned shifted;
    for( int j=0; j<4; j++ ) { 
      shifted = (valC>>(j*16)) & 0xffff;
      shifted |= (valA<<16);
      ram0.push_back(shifted);
      shifted = (valB>>(j*16)) & 0xffff;
      shifted |= (valA<<16);
      ram1.push_back(shifted);
    }
  } 

  for( int i=0; i<ram0.size(); i++ ) { 
      std::cout << std::dec << i << "\t"
		<< "ram0 :: " << std::hex << ram0[i]  << "\t"
		<< "ram1 :: " << std::hex << ram1[i] 
		<< std::endl;  
  }

  char strA[256],strB[256];
  if( channel == 0 )  { 
    sprintf(strA,"sender.sriram0.addr");
    sprintf(strB,"sender.sriram1.addr");
  } else {
    sprintf(strA,"sender.sriram2.addr");
    sprintf(strB,"sender.sriram3.addr");
  }
  hw.getNode(strA).write(0x0);
  hw.getNode(strB).write(0x0);
  hw.dispatch();
  
  if( channel == 0 )  { 
    sprintf(strA,"sender.sriram0.data");
    sprintf(strB,"sender.sriram1.data");
  } else {
    sprintf(strA,"sender.sriram2.data");
    sprintf(strB,"sender.sriram3.data");
  }
  hw.getNode(strA).writeBlock(ram0);
  hw.getNode(strB).writeBlock(ram1);
  hw.dispatch();

  free(str);
  return ram0.size()/4;

}



int 
load_cd_fifo(uhal::HwInterface & hw, const char * fname, int channel)
{ 
  FILE * f = fopen(fname,"r"); 
  size_t len; 

  char *str = (char *)malloc(1024*sizeof(char)); 
 
  unsigned valA;
  uint64_t valB;
  std::vector<uint32_t> ram;
  int count=0;


  bool found_data = false;
  while( !feof(f) ) {  

    int nlen = getline( &str, &len, f ); 
    if( !strncmp(str,"#",1) ) continue;
    if( !strncmp(str,"\n",1)  ) { 
      for( int i=0; i<4&&found_data; i++ ) {
	ram.push_back(0);
      }
      continue; 
    } 

    found_data = true;
    sscanf(str,"%x %llx", &valA, &valB  ); 
    std::cout  << std::dec << count << " "
	       << std::hex << std::setfill('0') 
	       << std::setw(1)  << valA << " " 
	       << std::setw(16) << valB << " " 
	       << std::endl; 
    count++;

    unsigned shifted;
    for( int j=0; j<4; j++ ) { 
      shifted = (valB>>(j*18)) & 0x3ffff;
      if( j == 3 ) shifted |= (valA<<10);
      ram.push_back(shifted);
    }
  } 

  for( int i=0; i<ram.size(); i++ ) { 
      std::cout << std::dec << i << "\t"
		<< "ram :: " << std::hex << ram[i]  << "\t"
		<< std::endl;  
  }

  char strA[256];
  // reset addr
  sprintf(strA,"sender.channel%d.cdfifo.ram.addr",channel);
  hw.getNode(strA).write(0x0);
  hw.dispatch();
  //
  sprintf(strA,"sender.channel%d.cdfifo.ram.data",channel);
  hw.getNode(strA).writeBlock(ram);
  hw.dispatch();
  //

  return ram.size()/4;

}


int 
load_ttc_fifo(uhal::HwInterface & hw, const char * fname, int channel)
{ 
  FILE * f = fopen(fname,"r"); 
  size_t len; 

  char *str = (char *)malloc(1024*sizeof(char)); 
 
  uint64_t valA, valB, valC;
  std::vector<uint32_t> ram0,ram1;
  int count=0;



  while( !feof(f) ) {  

    int nlen = getline( &str, &len, f ); 
    if( !strncmp(str,"#",1) or !strncmp(str,"\n",1)  ) { 
      continue; 
    } 
    sscanf(str,"%llx %llx", &valA, &valB  ); 
    std::cout  << std::dec << count << " "
	       << std::hex << std::setfill('0') 
	       << std::setw(16) << valA << " " 
	       << std::setw(16) << valB << " " 
	       << std::endl; 
    count++;

    unsigned shifted;
    for( int j=0; j<4; j++ ) { 
      shifted = (valA>>(j*18)) & 0x3ffff;
      ram1.push_back(shifted);
      shifted = (valB>>(j*18)) & 0x3ffff;
      ram0.push_back(shifted);
    }
  } 

  for( int i=0; i<ram1.size(); i++ ) { 
      std::cout << std::dec << i << "\t"
		<< "ram1 :: " << std::hex << ram1[i]  << "\t"
		<< "ram0 :: " << std::hex << ram0[i]  << "\t"
		<< std::endl;  
  }

  char strA[256];
  // reset addr
  sprintf(strA,"sender.channel%d.ttcfifo.ram0.addr",channel);
  hw.getNode(strA).write(0x0);
  sprintf(strA,"sender.channel%d.ttcfifo.ram1.addr",channel);
  hw.getNode(strA).write(0x0);
  hw.dispatch();
  //
  sprintf(strA,"sender.channel%d.ttcfifo.ram0.data",channel);
  hw.getNode(strA).writeBlock(ram0);
  hw.dispatch();
  sprintf(strA,"sender.channel%d.ttcfifo.ram1.data",channel);
  hw.getNode(strA).writeBlock(ram1);
  hw.dispatch();

  sprintf(strA,"sender.channel%d.ttcfifo.csr.ctrl",channel);
  hw.getNode(strA).write(0x60000000 + ram0.size()/4);

  hw.dispatch();


  return ram0.size()/4;

}
