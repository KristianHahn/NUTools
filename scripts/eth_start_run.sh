# 
# for bandwidth scanning from PC 
# 
 
#!/bin/sh 
 
run_in_dec=$1 
run_in_hex=`echo "obase=16; ${run_in_dec}" | bc`; 
 
# pkgdir set by ssh env 
source ./scripts/env.sh 
export NU_TOOLS_XML=file:///${PKGDIR}/addrtab 

 
# disable payload generation (or FE equiv)
regtool.exe -dx1 -rpayload.ctrl.reg.en 0 
 
# disable the link 
regtool.exe -dx1 -reth10g.ctrl.reg.rst  1 
echo "    * link disabled"; 

# configure the eth interface
regtool.exe -dx1 -reth10g.ctrl.local_ip     0xC0A80352
regtool.exe -dx1 -reth10g.ctrl.remote_ip    0xC0A80302
regtool.exe -dx1 -reth10g.ctrl.ports.local  0x04D2
regtool.exe -dx1 -reth10g.ctrl.ports.remote 0x04D2
regtool.exe -dx1 -reth10g.ctrl.reg.run      ${run_in_hex}


# small pkt aggregation
regtool.exe -dx1 -reth10g.ctrl.reg.aggregate 1
regtool.exe -dx1 -reth10g.ctrl.reg.aggregate_limit 0x101

 # enable hearbeat (order and need a delay for tif  ...)
regtool.exe -dx1 -reth10g.ctrl.heartbeat_threshold 0x13000000
sleep 2;
regtool.exe -dx1 -reth10g.ctrl.reg.heartbeat 1


#output for PC
echo -n "    * "; hostname
echo -n "    * "; regtool.exe -dx1 -reth10g.ctrl.reg.run | tail -1 
 
# reenable the link  
regtool.exe -dx1 -reth10g.ctrl.reg.rst  0 
echo  "    * link enabled"; 

# reenable payload generation (or FE equiv)
regtool.exe -dx1 -rpayload.ctrl.reg.en 1 

