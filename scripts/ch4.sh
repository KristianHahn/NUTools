#!/bin/sh

./ramtool.exe -dapollo.c2c.vu7p -rsender.ram0.data 0x00; sleep 2;
./ramtool.exe -dapollo.c2c.vu7p -rsender.ram1.data 0x10; sleep 2;
./ramtool.exe -dapollo.c2c.vu7p -rsender.ram2.data 0x20; sleep 2;
./ramtool.exe -dapollo.c2c.vu7p -rsender.ram3.data 0x30; sleep 2;
./regtool.exe -dapollo.c2c.vu7p -rsender.ram_data_size 7; sleep 2;

cd slink-ipbus-software
./bin/daq_on 256; sleep 2;
./bin/daq_on 272; sleep 2;
./bin/daq_on 288; sleep 2;
./bin/daq_on 304; sleep 2;
./bin/link_status 
cd -

#./ramtool.exe -dapollo.c2c.vu7p -rreceiver.ram0.data > r0.dat; sleep 1;
#./ramtool.exe -dapollo.c2c.vu7p -rreceiver.ram1.data > r1.dat; sleep 1;
#./ramtool.exe -dapollo.c2c.vu7p -rreceiver.ram2.data > r2.dat; sleep 1;
#./ramtool.exe -dapollo.c2c.vu7p -rreceiver.ram3.data > r3.dat; sleep 1;
