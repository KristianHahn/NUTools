#!/bin/bash

CTRL_INPUT=0x8
CTRL_ENABLE=0x4
CTRL_CAPTURE=0x1


# load the ipbus input buffers
mgttool.exe -dapollo.c2c.vu7p -q1  -c0  -brx -p0x0; sleep 1;
mgttool.exe -dapollo.c2c.vu7p -q1  -c1  -brx -p0x1; sleep 1;
mgttool.exe -dapollo.c2c.vu7p -q1  -c2  -brx -p0x2; sleep 1;
mgttool.exe -dapollo.c2c.vu7p -q1  -c3  -brx -p0x3; sleep 1;
#
mgttool.exe -dapollo.c2c.vu7p -q2  -c0  -brx -p0x4; sleep 1;
mgttool.exe -dapollo.c2c.vu7p -q2  -c1  -brx -p0x5; sleep 1;
mgttool.exe -dapollo.c2c.vu7p -q2  -c2  -brx -p0x6; sleep 1;
mgttool.exe -dapollo.c2c.vu7p -q2  -c3  -brx -p0x7; sleep 1;
#
mgttool.exe -dapollo.c2c.vu7p -q3  -c0  -brx -p0x8; sleep 1;
mgttool.exe -dapollo.c2c.vu7p -q3  -c1  -brx -p0x9; sleep 1;
mgttool.exe -dapollo.c2c.vu7p -q3  -c2  -brx -p0xa; sleep 1;
mgttool.exe -dapollo.c2c.vu7p -q3  -c3  -brx -p0xb; sleep 1;
#
mgttool.exe -dapollo.c2c.vu7p -q5  -c0  -brx -p0xc; sleep 1;
mgttool.exe -dapollo.c2c.vu7p -q5  -c1  -brx -p0xd; sleep 1;
mgttool.exe -dapollo.c2c.vu7p -q5  -c2  -brx -p0xe; sleep 1;
mgttool.exe -dapollo.c2c.vu7p -q5  -c3  -brx -p0xf; sleep 1;
#
mgttool.exe -dapollo.c2c.vu7p -q6  -c0  -brx -p0x0; sleep 1;
mgttool.exe -dapollo.c2c.vu7p -q6  -c1  -brx -p0x1; sleep 1;
mgttool.exe -dapollo.c2c.vu7p -q6  -c2  -brx -p0x2; sleep 1;
mgttool.exe -dapollo.c2c.vu7p -q6  -c3  -brx -p0x3; sleep 1;
#
mgttool.exe -dapollo.c2c.vu7p -q12 -c0  -brx -p0x4; sleep 1;
mgttool.exe -dapollo.c2c.vu7p -q12 -c1  -brx -p0x5; sleep 1;
mgttool.exe -dapollo.c2c.vu7p -q12 -c2  -brx -p0x6; sleep 1;
mgttool.exe -dapollo.c2c.vu7p -q12 -c3  -brx -p0x7; sleep 1;
#
mgttool.exe -dapollo.c2c.vu7p -q13 -c0  -brx -p0x8; sleep 1;
mgttool.exe -dapollo.c2c.vu7p -q13 -c1  -brx -p0x9; sleep 1;
mgttool.exe -dapollo.c2c.vu7p -q13 -c2  -brx -p0xa; sleep 1;
mgttool.exe -dapollo.c2c.vu7p -q13 -c3  -brx -p0xb; sleep 1;
#
mgttool.exe -dapollo.c2c.vu7p -q15 -c0  -brx -p0xc; sleep 1;
mgttool.exe -dapollo.c2c.vu7p -q15 -c1  -brx -p0xd; sleep 1;
mgttool.exe -dapollo.c2c.vu7p -q15 -c2  -brx -p0xe; sleep 1;
mgttool.exe -dapollo.c2c.vu7p -q15 -c3  -brx -p0xf; sleep 1;
#
mgttool.exe -dapollo.c2c.vu7p -q16 -c0  -brx -p0x0; sleep 1;
mgttool.exe -dapollo.c2c.vu7p -q16 -c1  -brx -p0x1; sleep 1;
mgttool.exe -dapollo.c2c.vu7p -q16 -c2  -brx -p0x2; sleep 1;
mgttool.exe -dapollo.c2c.vu7p -q16 -c3  -brx -p0x3; sleep 1;
#
mgttool.exe -dapollo.c2c.vu7p -q17 -c0  -brx -p0x4; sleep 1;
mgttool.exe -dapollo.c2c.vu7p -q17 -c1  -brx -p0x5; sleep 1;
mgttool.exe -dapollo.c2c.vu7p -q17 -c2  -brx -p0x6; sleep 1;
mgttool.exe -dapollo.c2c.vu7p -q17 -c3  -brx -p0x7; sleep 1;



# capture the data using :
echo "now run :: mgttool.exe -dapollo.c2c.vu7p -q1 -c0 -btx --capture  | less"


