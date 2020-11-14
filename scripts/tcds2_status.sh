#!/bin/bash
echo""

echo -n "HP clock: " 
regtool.exe -dapollo.c2c.vu7p -rfreq.ctrl.chan_sel 3 > /dev/null;
sleep 1;
val=`regtool.exe -dapollo.c2c.vu7p -rfreq.freq.count | tail -1 | awk '{print $3}'` 
freq.sh $val | tail -1 
echo -n "LHC clock: " 
regtool.exe -dapollo.c2c.vu7p -rfreq.ctrl.chan_sel 1 > /dev/null;
sleep 1;
val=`regtool.exe -dapollo.c2c.vu7p -rfreq.freq.count | tail -1 | awk '{print $3}'` 
freq.sh $val | tail -1 
echo ""

if [ "x$1" == "x1" ]; then
	echo -n "resetting MGT ... "
	regtool.exe -dapollo.c2c.vu7p -rtcds2.csr.control.mgt_reset_all 0 > /dev/null; sleep 1;
	regtool.exe -dapollo.c2c.vu7p -rtcds2.csr.control.mgt_reset_all 1 > /dev/null; sleep 1;
	regtool.exe -dapollo.c2c.vu7p -rtcds2.csr.control.mgt_reset_all 0 > /dev/null; sleep 1;
	regtool.exe -dapollo.c2c.vu7p -rtcds2.csr.control.mgt_reset_tx 0 > /dev/null; sleep 1;
	regtool.exe -dapollo.c2c.vu7p -rtcds2.csr.control.mgt_reset_tx 1 > /dev/null; sleep 1;
	regtool.exe -dapollo.c2c.vu7p -rtcds2.csr.control.mgt_reset_tx 0 > /dev/null; sleep 1;
	regtool.exe -dapollo.c2c.vu7p -rtcds2.csr.control.mgt_reset_rx 0 > /dev/null; sleep 1;
	regtool.exe -dapollo.c2c.vu7p -rtcds2.csr.control.mgt_reset_rx 1 > /dev/null; sleep 1;
	regtool.exe -dapollo.c2c.vu7p -rtcds2.csr.control.mgt_reset_rx 0 > /dev/null; sleep 1;
	echo " done"; echo "";
fi;

echo "tcds2 interface config: "
val=`regtool.exe -dapollo.c2c.vu7p -rtcds2.csr.status.has_spy_registers | tail -1 | awk '{print $3}'`
echo "has_spy_registers : $val"
val=`regtool.exe -dapollo.c2c.vu7p -rtcds2.csr.status.is_link_speed_10g | tail -1 | awk '{print $3}'`
echo "is_link_speed_10g : $val"
val=`regtool.exe -dapollo.c2c.vu7p -rtcds2.csr.status.has_link_test_mode | tail -1 | awk '{print $3}'`
echo "has_link_test_mode : $val"
echo "" 

echo "MGT status: "
regtool.exe -dapollo.c2c.vu7p -rtcds2.csr.status.mgt_power_good | tail -1
regtool.exe -dapollo.c2c.vu7p -rtcds2.csr.status.mgt_tx_pll_lock | tail -1 
regtool.exe -dapollo.c2c.vu7p -rtcds2.csr.status.mgt_rx_pll_lock | tail -1 
regtool.exe -dapollo.c2c.vu7p -rtcds2.csr.status.mgt_reset_tx_done | tail -1 
regtool.exe -dapollo.c2c.vu7p -rtcds2.csr.status.mgt_reset_rx_done | tail -1 
regtool.exe -dapollo.c2c.vu7p -rtcds2.csr.status.mgt_tx_ready | tail -1 
regtool.exe -dapollo.c2c.vu7p -rtcds2.csr.status.mgt_rx_ready | tail -1 
regtool.exe -dapollo.c2c.vu7p -rtcds2.csr.status.rx_frame_locked | tail -1 
regtool.exe -dapollo.c2c.vu7p -rtcds2.csr.status.rx_frame_unlock_counter | tail -1 
echo ""

echo "Orbit: "
regtool.exe -dapollo.c2c.vu7p -rmisc.status.orbit_counter | tail -1 
regtool.exe -dapollo.c2c.vu7p -rmisc.status.bx_between_orbit_signals | tail -1 
echo ""

echo "RX spy: "
val0=`regtool.exe -dapollo.c2c.vu7p -rtcds2.spy_frame_rx.word0 | tail -1 | awk '{print $3}'` 
val1=`regtool.exe -dapollo.c2c.vu7p -rtcds2.spy_frame_rx.word1 | tail -1 | awk '{print $3}'` 
val2=`regtool.exe -dapollo.c2c.vu7p -rtcds2.spy_frame_rx.word2 | tail -1 | awk '{print $3}'` 
val3=`regtool.exe -dapollo.c2c.vu7p -rtcds2.spy_frame_rx.word3 | tail -1 | awk '{print $3}'` 
echo "$val0 $val1 $val2 $val3"
val4=`regtool.exe -dapollo.c2c.vu7p -rtcds2.spy_frame_rx.word4 | tail -1 | awk '{print $3}'` 
val5=`regtool.exe -dapollo.c2c.vu7p -rtcds2.spy_frame_rx.word5 | tail -1 | awk '{print $3}'` 
val6=`regtool.exe -dapollo.c2c.vu7p -rtcds2.spy_frame_rx.word6 | tail -1 | awk '{print $3}'` 
val7=`regtool.exe -dapollo.c2c.vu7p -rtcds2.spy_frame_rx.word7 | tail -1 | awk '{print $3}'` 
echo "$val0 $val1 $val2 $val3"
echo ""


echo "TTC: " 
regtool.exe -dapollo.c2c.vu7p -rtcds2.spy_ttc2_channel0.status_info | tail -1 
regtool.exe -dapollo.c2c.vu7p -rtcds2.spy_ttc2_channel0.reserved | tail -1 
regtool.exe -dapollo.c2c.vu7p -rtcds2.spy_ttc2_channel1.status_info | tail -1 
regtool.exe -dapollo.c2c.vu7p -rtcds2.spy_ttc2_channel1.reserved | tail -1 
echo ""

