#include "ttcargs.h"
#include "ttcroutines.h"

void ttc_reset(HwInterface & hw, DevStruct dev) {

  std::cout << "resetting the TTC block ... " << std::endl;

  hw.getNode("ctrl.csr.ctrl.soft_rst").write(1);
  hw.dispatch();
  usleep(1000);
  
  hw.getNode( "ctrl.csr.ctrl.clk40_rst" ).write(1);
  hw.dispatch();
  usleep(1000);
  
  hw.getNode( "ctrl.csr.ctrl.clk40_sel" ).write(1);
  hw.getNode( "ctrl.csr.ctrl.clk40_rst" ).write(0);
  hw.dispatch();
  
  hw.getNode( "ttc.csr.ctrl.rst" ).write(1);
  hw.dispatch();
  usleep(1000);
  hw.getNode( "ttc.csr.ctrl.rst" ).write(0);
  hw.dispatch();

  if( dev.ttcext ) {   
    hw.getNode ( "ttc.csr.ctrl.ttc_enable" ).write(1); 
    hw.getNode ( "ttc.csr.ctrl.int_bc0_enable" ).write(0); 
  } else { 
    hw.getNode ( "ttc.csr.ctrl.ttc_enable" ).write(0); 
    hw.getNode ( "ttc.csr.ctrl.int_bc0_enable" ).write(1); 
  }
  hw.dispatch();
  
  // clear ctrs
  hw.getNode("ttc.csr.ctrl.err_ctr_clear").write(1);
  hw.getNode("ttc.csr.ctrl.err_ctr_clear").write(0);
  hw.getNode("ttc.csr.ctrl.ctr_clear").write(1);
  hw.getNode("ttc.csr.ctrl.ctr_clear").write(0);
  hw.dispatch();
}


void ttc_dump(HwInterface & hw, DevStruct dev) {

  ValWord< uint32_t > ttc_enable = hw.getNode ( "ttc.csr.ctrl.ttc_enable" ).read(); 
  ValWord< uint32_t > int_bc0_enable = hw.getNode ( "ttc.csr.ctrl.int_bc0_enable" ).read(); 

  ValWord< uint32_t > clk40_lock   = hw.getNode ( "ctrl.csr.stat.clk40_lock" ).read();    
  ValWord< uint32_t > bc0_lock     = hw.getNode ( "ttc.csr.stat0.bc0_lock" ).read();    
  ValWord< uint32_t > dist_lock    = hw.getNode ( "ttc.csr.stat0.dist_lock" ).read();    
  ValWord< uint32_t > ttc_phase_ok = hw.getNode ( "ttc.csr.stat0.ttc_phase_ok" ).read();    

  hw.dispatch();
  
  std::cout << std::endl;
  std::cout << "----------------------" << std::endl;
  std::cout << "ttc_enable   : " << ttc_enable << std::endl;
  std::cout << "int_bc0_enable   : " << int_bc0_enable << std::endl;
  std::cout << std::endl;
  std::cout << "clk40_lock   : " << clk40_lock << std::endl;
  std::cout << "bc0_lock     : " << bc0_lock << std::endl;
  std::cout << "dist_lock    : " << dist_lock << std::endl;
  std::cout << "ttc_phase_ok : " << ttc_phase_ok << std::endl;
  std::cout << "----------------------" << std::endl;
  std::cout << std::endl;
}
