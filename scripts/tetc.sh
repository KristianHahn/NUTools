#!/bin/bash

CTRL_INPUT=0x8
CTRL_ENABLE=0x4
CTRL_CAPTURE=0x1

poke 0x40020008 0x3; poke 0x40020008 0x0; poke 0x40020008 0x3;
./ttctool.exe -dyuge.c2c.0 -v -x0;

# load the ipbus input buffers
./mgttool.exe -dyuge.c2c.0 -q0 -c0  -brx -p -fmemfiles.bugfix/memfile_TE_0.dat ; 
./mgttool.exe -dyuge.c2c.0 -q0 -c1  -brx -p -fmemfiles.bugfix/memfile_TE_1.dat ; 
./mgttool.exe -dyuge.c2c.0 -q0 -c2  -brx -p -fmemfiles.bugfix/memfile_TE_2.dat ; 
./mgttool.exe -dyuge.c2c.0 -q0 -c3  -brx -p -fmemfiles.bugfix/memfile_TE_3.dat ; 
./mgttool.exe -dyuge.c2c.0 -q1 -c0  -brx -p -fmemfiles.bugfix/memfile_TE_4.dat ; 
./mgttool.exe -dyuge.c2c.0 -q1 -c1  -brx -p -fmemfiles.bugfix/memfile_TE_5.dat ; 
./mgttool.exe -dyuge.c2c.0 -q1 -c2  -brx -p -fmemfiles.bugfix/memfile_TE_6.dat ; 
./mgttool.exe -dyuge.c2c.0 -q1 -c3  -brx -p -fmemfiles.bugfix/memfile_TE_7.dat ; 
./mgttool.exe -dyuge.c2c.0 -q2 -c0  -brx -p -fmemfiles.bugfix/memfile_TE_8.dat ; 
./mgttool.exe -dyuge.c2c.0 -q2 -c1  -brx -p -fmemfiles.bugfix/memfile_TE_9.dat ; 
./mgttool.exe -dyuge.c2c.0 -q2 -c2  -brx -p -fmemfiles.bugfix/memfile_TE_10.dat ; 
./mgttool.exe -dyuge.c2c.0 -q2 -c3  -brx -p -fmemfiles.bugfix/memfile_TE_11.dat ; 
./mgttool.exe -dyuge.c2c.0 -q3 -c0  -brx -p -fmemfiles.bugfix/memfile_TE_12.dat ;

# play into the TE memories
./regtool.exe -dyuge.c2c.0 -rpayload.csr.ctrl0.TE_ctrl ${CTRL_INPUT}
# start the TEs processing
./regtool.exe -dyuge.c2c.0 -rpayload.csr.ctrl0.TE_ctrl ${CTRL_ENABLE}
# play TE results out of the payload 
./regtool.exe -dyuge.c2c.0 -rpayload.csr.ctrl0.TE_ctrl ${CTRL_CAPTURE}


# start the TC
./regtool.exe -dyuge.c2c.0 -rpayload.csr.ctrl0.TC_ctrl ${CTRL_ENABLE}
# play TC results out of the payload
./regtool.exe -dyuge.c2c.0 -rpayload.csr.ctrl0.TC_ctrl ${CTRL_CAPTURE}


# capture the data using :
# the TEs, eg: TE#0 on quad 0, channel 0 
#./mgttool.exe -dyuge.c2c.0 -q0 -c0 -btx --capture  | less
# the TC
#./mgttool.exe -dyuge.c2c.0 -q3 -c1 -btx --capture  | less

