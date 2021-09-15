#!/bin/sh

# diable payload generation
regtool.exe -dx1 -rpayload.ctrl.reg.en 0

# configure th interface
regtool.exe -dx1 -reth10g.ctrl.local_ip C0A80352
regtool.exe -dx1 -reth10g.ctrl.remote_ip C0A80302
regtool.exe -dx1 -reth10g.ctrl.ports.local 04D2
regtool.exe -dx1 -reth10g.ctrl.ports.remote 04D2

# enable the echo server
regtool.exe -dx1 -reth10g.ctrl.reg.echo  1

