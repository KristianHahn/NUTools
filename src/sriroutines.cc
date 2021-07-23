#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <vector>
#include "sriroutines.h"

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
    sprintf(strA,"slink.bypass_ram_0.addr");
    sprintf(strB,"slink.bypass_ram_1.addr");
  } else {
    sprintf(strA,"slink.bypass_ram_2.addr");
    sprintf(strB,"slink.bypass_ram_3.addr");
  }
  hw.getNode(strA).write(0x0);
  hw.getNode(strB).write(0x0);
  hw.dispatch();
  
  if( channel == 0 )  { 
    sprintf(strA,"slink.bypass_ram_0.data");
    sprintf(strB,"slink.bypass_ram_1.data");
  } else {
    sprintf(strA,"slink.bypass_ram_2.data");
    sprintf(strB,"slink.bypass_ram_3.data");
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
  sprintf(strA,"slink.channel_%d.cdfifo.ram.addr",channel);
  hw.getNode(strA).write(0x0);
  hw.dispatch();
  //
  sprintf(strA,"slink.channel_%d.cdfifo.ram.data",channel);
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
  sprintf(strA,"slink.channel_%d.ttcfifo.ram0.addr",channel);
  hw.getNode(strA).write(0x0);
  sprintf(strA,"slink.channel_%d.ttcfifo.ram1.addr",channel);
  hw.getNode(strA).write(0x0);
  hw.dispatch();
  //
  sprintf(strA,"slink.channel_%d.ttcfifo.ram0.data",channel);
  hw.getNode(strA).writeBlock(ram0);
  hw.dispatch();
  sprintf(strA,"slink.channel_%d.ttcfifo.ram1.data",channel);
  hw.getNode(strA).writeBlock(ram1);
  hw.dispatch();

  sprintf(strA,"slink.channel_%d.ttcfifo.csr.ctrl",channel);
  hw.getNode(strA).write(0x60000000 + ram0.size()/4);

  hw.dispatch();


  return ram0.size()/4;

}
