#!/bin/bash

CTRL_INPUT=0x8
CTRL_ENABLE=0x4
CTRL_CAPTURE=0x1

./ttctool.exe -dapollo.c2c.vu7p -v -x0;

# load the ipbus input buffers
./mgttool.exe -dapollo.c2c.vu7p -q1 -c0  -brx -p -fmemfiles.bugfix/memfile_TE_0.dat ; sleep 1;
./mgttool.exe -dapollo.c2c.vu7p -q1 -c1  -brx -p -fmemfiles.bugfix/memfile_TE_1.dat ; sleep 1;
./mgttool.exe -dapollo.c2c.vu7p -q1 -c2  -brx -p -fmemfiles.bugfix/memfile_TE_2.dat ; sleep 1;
./mgttool.exe -dapollo.c2c.vu7p -q1 -c3  -brx -p -fmemfiles.bugfix/memfile_TE_3.dat ; sleep 1;
./mgttool.exe -dapollo.c2c.vu7p -q2 -c0  -brx -p -fmemfiles.bugfix/memfile_TE_4.dat ; sleep 1;
./mgttool.exe -dapollo.c2c.vu7p -q2 -c1  -brx -p -fmemfiles.bugfix/memfile_TE_5.dat ; sleep 1;
./mgttool.exe -dapollo.c2c.vu7p -q2 -c2  -brx -p -fmemfiles.bugfix/memfile_TE_6.dat ; sleep 1;
./mgttool.exe -dapollo.c2c.vu7p -q2 -c3  -brx -p -fmemfiles.bugfix/memfile_TE_7.dat ; sleep 1;
./mgttool.exe -dapollo.c2c.vu7p -q3 -c0  -brx -p -fmemfiles.bugfix/memfile_TE_8.dat ; sleep 1;
./mgttool.exe -dapollo.c2c.vu7p -q3 -c1  -brx -p -fmemfiles.bugfix/memfile_TE_9.dat ; sleep 1;
./mgttool.exe -dapollo.c2c.vu7p -q3 -c2  -brx -p -fmemfiles.bugfix/memfile_TE_10.dat ; sleep 1;
./mgttool.exe -dapollo.c2c.vu7p -q3 -c3  -brx -p -fmemfiles.bugfix/memfile_TE_11.dat ; sleep 1;
./mgttool.exe -dapollo.c2c.vu7p -q4 -c0  -brx -p -fmemfiles.bugfix/memfile_TE_12.dat ;sleep 1;

# play into the TE memories
./regtool.exe -dapollo.c2c.vu7p -rpayload.csr.ctrl0.TE_ctrl ${CTRL_INPUT}
sleep 1;
# start the TEs processing
./regtool.exe -dapollo.c2c.vu7p -rpayload.csr.ctrl0.TE_ctrl ${CTRL_ENABLE}
sleep 1;
# play TE results out of the payload 
./regtool.exe -dapollo.c2c.vu7p -rpayload.csr.ctrl0.TE_ctrl ${CTRL_CAPTURE}
sleep 1;

# start the TC
./regtool.exe -dapollo.c2c.vu7p -rpayload.csr.ctrl0.TC_ctrl ${CTRL_ENABLE}
sleep 1;
# play TC results out of the payload
./regtool.exe -dapollo.c2c.vu7p -rpayload.csr.ctrl0.TC_ctrl ${CTRL_CAPTURE}
sleep 1;

# capture the data using :
# the TEs, eg: TE#0 on quad 1, channel 0 
#./mgttool.exe -dapollo.c2c.vu7p -q1 -c0 -btx --capture  | less
# the TC
#./mgttool.exe -dapollo.c2c.vu7p -q4 -c1 -btx --capture  | less

