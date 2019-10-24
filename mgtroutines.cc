
#include "mgtargs.h"
#include "mgtroutines.h"

void mgt_global_reset(HwInterface & hw, DevStruct dev) {
  if( dev.reset == MGT_RESET_TOGGLE ) { 
    printf("reset toggling ...\n");
    hw.getNode ( "datapath.region.mgt.rw_regs.common.control.soft_reset" ).write(1);
    hw.getNode ( "datapath.region.mgt.rw_regs.common.control.reset_error_counter" ).write(1);
    hw.getNode ( "datapath.region.mgt.rw_regs.common.control.reset_tx_datapath" ).write(1);
    hw.getNode ( "datapath.region.mgt.rw_regs.common.control.reset_rx_datapath" ).write(1);
    hw.dispatch();
    usleep(1000);
    hw.getNode ( "datapath.region.mgt.rw_regs.common.control.soft_reset" ).write(0);
    hw.getNode ( "datapath.region.mgt.rw_regs.common.control.reset_error_counter" ).write(0);
    hw.getNode ( "datapath.region.mgt.rw_regs.common.control.reset_tx_datapath" ).write(0);
    hw.getNode ( "datapath.region.mgt.rw_regs.common.control.reset_rx_datapath" ).write(0);
    hw.dispatch();
  } else {
    printf("reset not toggling ...\n");
    hw.getNode ( "datapath.region.mgt.rw_regs.common.control.soft_reset" ).write(dev.reset);
    hw.getNode ( "datapath.region.mgt.rw_regs.common.control.reset_error_counter" ).write(dev.reset);
    hw.getNode ( "datapath.region.mgt.rw_regs.common.control.reset_tx_datapath" ).write(dev.reset);
    hw.getNode ( "datapath.region.mgt.rw_regs.common.control.reset_rx_datapath" ).write(dev.reset);
    hw.dispatch();
  }
}





//
// per-channel usr tx reset
//
void mgt_tx_usr_reset(HwInterface & hw,DevStruct dev) { 
  char str[256];
  if( dev.tx_usrrst == MGT_RESET_TOGGLE ) { 
    printf("tx toggling ... \n");
    for( int i=0; i<4; i++ ) { 
      if( (dev.channel>>i)&1UL ) { 
	sprintf(str,"datapath.region.mgt.rw_regs.ch%d.control.tx_usrrst", i);
	hw.getNode(str).write(1);
	hw.dispatch();
	usleep(1000);
	hw.getNode(str).write(0);
	hw.dispatch();
      }
    }
  } else {
    printf("tx not toggling ... writing %d\n",dev.tx_usrrst);
    for( int i=0; i<4; i++ ) { 
      if( (dev.channel>>i)&1UL ) { 
	sprintf(str,"datapath.region.mgt.rw_regs.ch%d.control.tx_usrrst", i);
	hw.getNode(str).write(dev.tx_usrrst);
	hw.dispatch();
      }
    }
  }
}


//
// per-channel usr rx reset
//
void mgt_rx_usr_reset(HwInterface & hw,DevStruct dev) {
  char str[256];
  if( dev.rx_usrrst == MGT_RESET_TOGGLE ) { 
    printf("rx toggling ... \n");
    for( int i=0; i<4; i++ ) { 
      if( (dev.channel>>i)&1UL ) { 
	sprintf(str,"datapath.region.mgt.rw_regs.ch%d.control.rx_usrrst", i);
	hw.getNode(str).write(1);
	hw.dispatch();
	usleep(1000);
	hw.getNode(str).write(0);
	hw.dispatch();
      }
    }
  } else {
    printf("rx not toggling ... writing %d\n", dev.rx_usrrst);
    for( int i=0; i<4; i++ ) { 
      if( (dev.channel>>i)&1UL ) { 
	sprintf(str,"datapath.region.mgt.rw_regs.ch%d.control.rx_usrrst", i);
	hw.getNode(str).write(dev.rx_usrrst);
	hw.dispatch();
      }
    }
  }
}


//
// per-channel crc error reset
//
void mgt_reset_crc_counters(HwInterface & hw,DevStruct dev) {
  char str[256];
  if( dev.reset_crc_counters == MGT_RESET_TOGGLE ) { 
    printf("crc toggling ... \n");
    for( int i=0; i<4; i++ ) { 
      if( (dev.channel>>i)&1UL ) { 
	sprintf(str,"datapath.region.mgt.rw_regs.ch%d.control.reset_crc_counters", i);
	hw.getNode(str).write(1);
	hw.dispatch();
	usleep(1000);
	hw.getNode(str).write(0);
	hw.dispatch();
      }
    }
  } 
  else {
    for( int i=0; i<4; i++ ) {
      if( (dev.channel>>i)&1UL ) {
  	sprintf(str,"datapath.region.mgt.rw_regs.ch%d.control.reset_crc_counters", i);
  	hw.getNode(str).write(dev.reset_crc_counters);
  	hw.dispatch();
      }
    }
  }
}


//
// per-channel loopback
//
void mgt_set_loopback(HwInterface & hw,DevStruct dev) { 
  char str[256];
  for( int i=0; i<4; i++ ) { 
    if( (dev.channel>>i)&1UL ) { 
      printf("datapath.region.mgt.rw_regs.ch%d.control.loopback\n", i);
      sprintf(str,"datapath.region.mgt.rw_regs.ch%d.control.loopback", i);
      hw.getNode(str).write(dev.loopback);
    }
  }
  hw.dispatch();
}

//
// dump mgt status
//
void mgt_dump(HwInterface & hw, DevStruct dev) {

  sleep(1);

  // Get status
  hw.getNode ( "datapath.ctrl.quad_sel" ).write(dev.quad_id);
  hw.dispatch();


  ValWord< uint32_t > link                 = hw.getNode ( "datapath.region.mgt.ro_regs.common.status.quad_link_status" ).read();
  ValWord< uint32_t > init_done            = hw.getNode ( "datapath.region.mgt.ro_regs.common.status.init_done" ).read();
  ValWord< uint32_t > reset_tx_done        = hw.getNode ( "datapath.region.mgt.ro_regs.common.status.reset_tx_done" ).read();
  ValWord< uint32_t > reset_rx_done        = hw.getNode ( "datapath.region.mgt.ro_regs.common.status.reset_rx_done" ).read();
  ValWord< uint32_t > bufferbypass_tx_done = hw.getNode ( "datapath.region.mgt.ro_regs.common.status.buffbypass_tx_done" ).read();
  ValWord< uint32_t > bufferbypass_rx_done = hw.getNode ( "datapath.region.mgt.ro_regs.common.status.buffbypass_rx_done" ).read();
  ValWord< uint32_t > qplllock             = hw.getNode ( "datapath.region.mgt.ro_regs.common.status.qplllock" ).read();

  ValWord< uint32_t > ch0_loopback    = hw.getNode( "datapath.region.mgt.rw_regs.ch0.control.loopback" ).read();
  ValWord< uint32_t > ch0_link        = hw.getNode( "datapath.region.mgt.ro_regs.ch0.status.link_status" ).read();
  ValWord< uint32_t > ch0_crc_error   = hw.getNode( "datapath.region.mgt.ro_regs.ch0.status.crc_error" ).read();
  ValWord< uint32_t > ch0_crc_checked = hw.getNode( "datapath.region.mgt.ro_regs.ch0.status.crc_checked" ).read();
  ValWord< uint32_t > ch0_tx_usrrst   = hw.getNode( "datapath.region.mgt.rw_regs.ch0.control.tx_usrrst" ).read();
  ValWord< uint32_t > ch0_rx_usrrst   = hw.getNode( "datapath.region.mgt.rw_regs.ch0.control.rx_usrrst" ).read();
  ValWord< uint32_t > ch0_crc_reset   = hw.getNode( "datapath.region.mgt.rw_regs.ch0.control.reset_crc_counters" ).read();

  ValWord< uint32_t > ch1_loopback    = hw.getNode( "datapath.region.mgt.rw_regs.ch1.control.loopback" ).read();
  ValWord< uint32_t > ch1_link        = hw.getNode( "datapath.region.mgt.ro_regs.ch1.status.link_status" ).read();
  ValWord< uint32_t > ch1_crc_error   = hw.getNode( "datapath.region.mgt.ro_regs.ch1.status.crc_error" ).read();
  ValWord< uint32_t > ch1_crc_checked = hw.getNode( "datapath.region.mgt.ro_regs.ch1.status.crc_checked" ).read();
  ValWord< uint32_t > ch1_tx_usrrst   = hw.getNode( "datapath.region.mgt.rw_regs.ch1.control.tx_usrrst" ).read();
  ValWord< uint32_t > ch1_rx_usrrst   = hw.getNode( "datapath.region.mgt.rw_regs.ch1.control.rx_usrrst" ).read();
  ValWord< uint32_t > ch1_crc_reset   = hw.getNode( "datapath.region.mgt.rw_regs.ch1.control.reset_crc_counters" ).read();

  ValWord< uint32_t > ch2_loopback    = hw.getNode( "datapath.region.mgt.rw_regs.ch2.control.loopback" ).read();
  ValWord< uint32_t > ch2_link        = hw.getNode( "datapath.region.mgt.ro_regs.ch2.status.link_status" ).read();
  ValWord< uint32_t > ch2_crc_error   = hw.getNode( "datapath.region.mgt.ro_regs.ch2.status.crc_error" ).read();
  ValWord< uint32_t > ch2_crc_checked = hw.getNode( "datapath.region.mgt.ro_regs.ch2.status.crc_checked" ).read();
  ValWord< uint32_t > ch2_tx_usrrst   = hw.getNode( "datapath.region.mgt.rw_regs.ch2.control.tx_usrrst" ).read();
  ValWord< uint32_t > ch2_rx_usrrst   = hw.getNode( "datapath.region.mgt.rw_regs.ch2.control.rx_usrrst" ).read();
  ValWord< uint32_t > ch2_crc_reset   = hw.getNode( "datapath.region.mgt.rw_regs.ch2.control.reset_crc_counters" ).read();

  ValWord< uint32_t > ch3_loopback    = hw.getNode( "datapath.region.mgt.rw_regs.ch3.control.loopback" ).read();
  ValWord< uint32_t > ch3_link        = hw.getNode( "datapath.region.mgt.ro_regs.ch3.status.link_status" ).read();
  ValWord< uint32_t > ch3_crc_error   = hw.getNode( "datapath.region.mgt.ro_regs.ch3.status.crc_error" ).read();
  ValWord< uint32_t > ch3_crc_checked = hw.getNode( "datapath.region.mgt.ro_regs.ch3.status.crc_checked" ).read();
  ValWord< uint32_t > ch3_tx_usrrst   = hw.getNode( "datapath.region.mgt.rw_regs.ch3.control.tx_usrrst" ).read();
  ValWord< uint32_t > ch3_rx_usrrst   = hw.getNode( "datapath.region.mgt.rw_regs.ch3.control.rx_usrrst" ).read();
  ValWord< uint32_t > ch3_crc_reset   = hw.getNode( "datapath.region.mgt.rw_regs.ch3.control.reset_crc_counters" ).read();

  hw.dispatch();
  std::cout << "==================================" << std::endl;
  std::cout << "Quad " << std::dec << dev.quad_id << std::endl;
  std::cout << "----------------------------------" << std::endl;
  std::cout << std::hex;
  std::cout << "quad_link_status   = " << link.value() << std::endl;
  std::cout << "init_done          = " << init_done.value() << std::endl;       
  std::cout << "reset_tx_done      = " << reset_tx_done.value() << std::endl;   
  std::cout << "reset_rx_done      = " << reset_rx_done.value() << std::endl;   
  std::cout << "buffbypass_tx_done = " << bufferbypass_tx_done.value() << std::endl;    
  std::cout << "buffbypass_rx_done = " << bufferbypass_rx_done.value() << std::endl;    
  std::cout << "qplllock           = " << qplllock.value() << std::endl;  
  std::cout << "                 ch0   ch1   ch2   ch3" << std::endl;
  std::cout << "  loopback:      " << std::setw(3) << ch0_loopback    << "   " << std::setw(3) << ch1_loopback    << "   " << std::setw(3) << ch2_loopback    << "   " << std::setw(3) << ch3_loopback    << std::endl;
  std::cout << "  link_status:   " << std::setw(3) << ch0_link        << "   " << std::setw(3) << ch1_link        << "   " << std::setw(3) << ch2_link        << "   " << std::setw(3) << ch3_link        << std::endl;
  std::cout << "  crc_error:     " << std::setw(3) << ch0_crc_error   << "   " << std::setw(3) << ch1_crc_error   << "   " << std::setw(3) << ch2_crc_error   << "   " << std::setw(3) << ch3_crc_error   << std::endl;
  std::cout << "  crc_checked:   " << std::setw(3) << ch0_crc_checked << "   " << std::setw(3) << ch1_crc_checked << "   " << std::setw(3) << ch2_crc_checked << "   " << std::setw(3) << ch3_crc_checked << std::endl;
  std::cout << "  tx_usrrst:     " << std::setw(3) << ch0_tx_usrrst << "   " << std::setw(3) << ch1_tx_usrrst << "   " << std::setw(3) << ch2_tx_usrrst << "   " << std::setw(3) << ch3_tx_usrrst << std::endl;
  std::cout << "  rx_usrrst:     " << std::setw(3) << ch0_rx_usrrst << "   " << std::setw(3) << ch1_rx_usrrst << "   " << std::setw(3) << ch2_rx_usrrst << "   " << std::setw(3) << ch3_rx_usrrst << std::endl;
  std::cout << "  crc_reset:     " << std::setw(3) << ch0_crc_reset << "   " << std::setw(3) << ch1_crc_reset << "   " << std::setw(3) << ch2_crc_reset << "   " << std::setw(3) << ch3_crc_reset << std::endl;
  std::cout << "==================================" << std::endl << std::endl;
  hw.dispatch();
};



void clearBuffer(HwInterface & hw, int quad, int chan, int bufftype) { 
  hw.getNode ( "datapath.ctrl.quad_sel" ).write(quad);
  hw.getNode ( "datapath.ctrl.chan_sel" ).write(chan);
  hw.getNode ( "datapath.ctrl.txrx_sel" ).write(bufftype);
  hw.dispatch();
  
  for( int i=0; i<BUFFER_LEN; i++ )  {
    hw.getNode ( "datapath.region.buffer.buffer.addr" ).write(i);
    hw.getNode ( "datapath.region.buffer.buffer.data" ).write(0x1);
    hw.dispatch();
  }
};

void writeBuffer(HwInterface & hw, int quad, int chan, int bufftype, std::vector<uint32_t> & data) { 
  hw.getNode ( "datapath.ctrl.quad_sel" ).write(quad);
  hw.getNode ( "datapath.ctrl.chan_sel" ).write(chan);
  hw.getNode ( "datapath.ctrl.txrx_sel" ).write(bufftype);
  hw.dispatch();
  
  for( unsigned int i=0; i<data.size()&&i<BUFFER_LEN; i++ )  {
    hw.getNode ( "datapath.region.buffer.buffer.addr" ).write(i);
    hw.getNode ( "datapath.region.buffer.buffer.data" ).write(data[i]);
    hw.dispatch();
  }
};



void readBuffer(HwInterface & hw, int quad, int chan, int bufftype, std::vector<uint32_t> & data, int len) { 
  hw.getNode ( "datapath.ctrl.quad_sel" ).write(quad);
  hw.getNode ( "datapath.ctrl.chan_sel" ).write(chan);
  hw.getNode ( "datapath.ctrl.txrx_sel" ).write(bufftype);
  hw.dispatch();

  usleep(10000);
  for( int i=0; i<len&&i<BUFFER_LEN; i++ )  {
    hw.getNode ( "datapath.region.buffer.buffer.addr" ).write(i);
    hw.dispatch();
    ValWord<uint32_t> val = hw.getNode ( "datapath.region.buffer.buffer.data" ).read();
    hw.dispatch();
    data.push_back(val);
  }
};





void mgt_play(HwInterface & hw,DevStruct dev) {
  vector<unsigned> txdata;
  for( int i=0; i<BUFFER_LEN/16; i++ ) { 
    txdata.push_back(0x00000000|dev.prefix);
    txdata.push_back(0x00000111|dev.prefix);
    txdata.push_back(0x00000222|dev.prefix);
    txdata.push_back(0x00010333|dev.prefix);
    txdata.push_back(0x00000444|dev.prefix);
    txdata.push_back(0x00000555|dev.prefix);
    txdata.push_back(0x00000666|dev.prefix);
    txdata.push_back(0x00010777|dev.prefix);
    txdata.push_back(0x00000888|dev.prefix);
    txdata.push_back(0x00000999|dev.prefix);
    txdata.push_back(0x00000aaa|dev.prefix);
    txdata.push_back(0x00010bbb|dev.prefix);
    txdata.push_back(0x00000ccc|dev.prefix);
    txdata.push_back(0x00000ddd|dev.prefix);
    txdata.push_back(0x00000eee|dev.prefix);
    txdata.push_back(0x00010fff|dev.prefix);
  }

  ValWord< uint32_t > linkup = hw.getNode ( "datapath.region.mgt.ro_regs.common.status.quad_link_status" ).read();
  hw.dispatch();
  while( !linkup ) {
    linkup = hw.getNode ( "datapath.region.mgt.ro_regs.common.status.quad_link_status" ).read();
    hw.dispatch();
    usleep(1000);
  }


  hw.getNode ( "ttc.csr.ctrl.ttc_enable" ).write(0); 
  hw.dispatch();
  hw.getNode ( "ttc.csr.ctrl.ttc_enable" ).write(1); 
  hw.dispatch();
  hw.getNode ( "ttc.csr.ctrl.int_bc0_enable" ).write(0); 
  hw.dispatch();
  hw.getNode ( "ttc.csr.ctrl.int_bc0_enable" ).write(1); 
  hw.dispatch();
  
  ValWord< uint32_t > bc0_en = hw.getNode ( "ttc.csr.ctrl.int_bc0_enable" ).read(); 
  hw.dispatch();


  clearBuffer(hw,dev.quad_id,dev.channel,kTX); 	// switches to tx
  usleep(10000);
  hw.dispatch();
  usleep(10000);
  hw.getNode ( "datapath.region.buffer.csr.mode.mode" ).write(MODE_PLAY); 
  hw.getNode ( "datapath.region.buffer.csr.mode.datasrc" ).write(SOURCE_BUFFER); 
  hw.getNode ( "datapath.region.buffer.csr.range.max_word" ).write(BUFFER_LEN);
  hw.getNode ( "datapath.region.buffer.csr.mode.stbsrc" ).write(STROBE_HIGH); 
  hw.dispatch();
  usleep(10000);
  writeBuffer(hw,dev.quad_id,dev.channel,kTX,txdata);



  // Play the buffers
  hw.getNode ( "ttc.csr.ctrl.ttc_sync_en" ).write(0); 
  hw.dispatch();
  usleep(10000); // <- this sleep is important !!!!

  hw.getNode ( "ttc.csr.ctrl.b_cmd" ).write(0xc); 
  hw.getNode ( "ttc.csr.ctrl.b_cmd_force" ).write(1); 
  hw.getNode ( "ttc.csr.ctrl.b_cmd_force" ).write(0); 
  hw.dispatch();	
}


void mgt_capture(HwInterface & hw,DevStruct dev) {
  vector<unsigned> rxdata;


  ValWord< uint32_t > linkup = hw.getNode ( "datapath.region.mgt.ro_regs.common.status.quad_link_status" ).read();
  hw.dispatch();
  while( !linkup ) {
    linkup = hw.getNode ( "datapath.region.mgt.ro_regs.common.status.quad_link_status" ).read();
    hw.dispatch();
    usleep(1000);
  }


  hw.getNode ( "ttc.csr.ctrl.ttc_enable" ).write(0); 
  hw.dispatch();
  hw.getNode ( "ttc.csr.ctrl.ttc_enable" ).write(1); 
  hw.dispatch();
  hw.getNode ( "ttc.csr.ctrl.int_bc0_enable" ).write(0); 
  hw.dispatch();
  hw.getNode ( "ttc.csr.ctrl.int_bc0_enable" ).write(1); 
  hw.dispatch();
  
  ValWord< uint32_t > bc0_en = hw.getNode ( "ttc.csr.ctrl.int_bc0_enable" ).read(); 
  hw.dispatch();


  clearBuffer(hw,dev.quad_id,dev.channel,kRX); /// switches to rx  
  hw.getNode ( "datapath.region.buffer.csr.mode.mode" ).write(MODE_CAPTURE); 
  hw.getNode ( "datapath.region.buffer.csr.mode.datasrc" ).write(SOURCE_INPUT); 
  hw.getNode ( "datapath.region.buffer.csr.range.max_word" ).write(BUFFER_LEN); 
  hw.getNode ( "datapath.region.buffer.csr.mode.stbsrc" ).write(STROBE_DATA); 
  hw.dispatch();	  



  // Capture the buffers
  hw.getNode ( "ttc.csr.ctrl.ttc_sync_en" ).write(0); 
  hw.dispatch();
  usleep(10000); // <- this sleep is important !!!!

  hw.getNode ( "ttc.csr.ctrl.b_cmd" ).write(0xc); 
  hw.getNode ( "ttc.csr.ctrl.b_cmd_force" ).write(1); 
  hw.getNode ( "ttc.csr.ctrl.b_cmd_force" ).write(0); 
  hw.dispatch();	

  std::cout << "\tQuad " << dev.quad_id  << std::endl;
  std::cout << "---------------------" << std::endl;
  readBuffer(hw,dev.quad_id,dev.channel,kRX,rxdata,BUFFER_LEN);
  for( int i=0; i<BUFFER_LEN; i++ ) {
    std::cout  << "i: "  << std::dec << std::setw(4) << i << "\t"
	       << "rx: " << std::hex << std::setw(5) << rxdata[i] << "\t\t"
	       << std::endl;
  }

}
