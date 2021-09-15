#!/bin/sh

# disable payload generation
regtool.exe -dx1 -rpayload.ctrl.reg.en 0

# disable the echo server 
regtool.exe -dx1 -reth10g.ctrl.reg.echo  0

# configue the payload generator
regtool.exe -dx1 -rpayload.ctrl.pause_interval 0x1
regtool.exe -dx1 -rpayload.ctrl.pkt_len 0xFF
# regtool.exe -dx1 -rpayload.ctrl.reg.decrement_len 0x1

# configure the eth interface
regtool.exe -dx1 -reth10g.ctrl.local_ip C0A80352
regtool.exe -dx1 -reth10g.ctrl.remote_ip C0A80302
regtool.exe -dx1 -reth10g.ctrl.ports.local 04D2
regtool.exe -dx1 -reth10g.ctrl.ports.remote 04D2

# enable payload generation
regtool.exe -dx1 -rpayload.ctrl.reg.en 1



