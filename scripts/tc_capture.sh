#!/bin/bash


# Tracket Parameters
./mgttool.exe -dapollo.c2c.vu7p -q4 -c1 -btx --capture > /dev/null;
sleep 1;
./mgttool.exe -dapollo.c2c.vu7p -q4 -c1 -btx --capture > tracklet_parameters.dat

# L3PHIB
./mgttool.exe -dapollo.c2c.vu7p -q4 -c2 -btx --capture > /dev/null;
sleep 1;
./mgttool.exe -dapollo.c2c.vu7p -q4 -c2 -btx --capture > tracklet_projections_L3PHIB.dat
# L3PHIC
./mgttool.exe -dapollo.c2c.vu7p -q4 -c3 -btx --capture > /dev/null;
sleep 1;
./mgttool.exe -dapollo.c2c.vu7p -q4 -c3 -btx --capture > tracklet_projections_L3PHIC.dat

# L4PHIB
./mgttool.exe -dapollo.c2c.vu7p -q5 -c0 -btx --capture > /dev/null;
sleep 1;
./mgttool.exe -dapollo.c2c.vu7p -q5 -c0 -btx --capture > tracklet_projections_L4PHIB.dat
# L4PHIC
./mgttool.exe -dapollo.c2c.vu7p -q5 -c1 -btx --capture > /dev/null;
sleep 1;
./mgttool.exe -dapollo.c2c.vu7p -q5 -c1 -btx --capture > tracklet_projections_L4PHIC.dat
# L4PHID
./mgttool.exe -dapollo.c2c.vu7p -q5 -c2 -btx --capture > /dev/null;
sleep 1;
./mgttool.exe -dapollo.c2c.vu7p -q5 -c2 -btx --capture > tracklet_projections_L4PHID.dat

# L5PHIB
./mgttool.exe -dapollo.c2c.vu7p -q5 -c3 -btx --capture > /dev/null;
sleep 1;
./mgttool.exe -dapollo.c2c.vu7p -q5 -c3 -btx --capture > tracklet_projections_L5PHIB.dat
# L5PHIC
./mgttool.exe -dapollo.c2c.vu7p -q6 -c0 -btx --capture > /dev/null;
sleep 1;
./mgttool.exe -dapollo.c2c.vu7p -q6 -c0 -btx --capture > tracklet_projections_L5PHIC.dat
# L5PHID
./mgttool.exe -dapollo.c2c.vu7p -q6 -c1 -btx --capture > /dev/null;
sleep 1;
./mgttool.exe -dapollo.c2c.vu7p -q6 -c1 -btx --capture > tracklet_projections_L5PHID.dat

# L6PHIB
./mgttool.exe -dapollo.c2c.vu7p -q6 -c2 -btx --capture > /dev/null;
sleep 1;
./mgttool.exe -dapollo.c2c.vu7p -q6 -c2 -btx --capture > tracklet_projections_L6PHIB.dat
# L6PHIC
./mgttool.exe -dapollo.c2c.vu7p -q6 -c3 -btx --capture > /dev/null;
sleep 1;
./mgttool.exe -dapollo.c2c.vu7p -q6 -c3 -btx --capture > tracklet_projections_L6PHIC.dat
# L6PHID
./mgttool.exe -dapollo.c2c.vu7p -q7 -c0 -btx --capture > /dev/null;
sleep 1;
./mgttool.exe -dapollo.c2c.vu7p -q7 -c0 -btx --capture > tracklet_projections_L6PHID.dat

# D1PHIB
./mgttool.exe -dapollo.c2c.vu7p -q7 -c1 -btx --capture > /dev/null;
sleep 1;
./mgttool.exe -dapollo.c2c.vu7p -q7 -c1 -btx --capture > tracklet_projections_D1PHIB.dat
# D1PHIC
./mgttool.exe -dapollo.c2c.vu7p -q7 -c2 -btx --capture > /dev/null;
sleep 1;
./mgttool.exe -dapollo.c2c.vu7p -q7 -c2 -btx --capture > tracklet_projections_D1PHIC.dat
# D1PHID
./mgttool.exe -dapollo.c2c.vu7p -q7 -c3 -btx --capture > /dev/null;
sleep 1;
./mgttool.exe -dapollo.c2c.vu7p -q7 -c3 -btx --capture > tracklet_projections_D1PHID.dat


# D2PHIB
./mgttool.exe -dapollo.c2c.vu7p -q8 -c0 -btx --capture > /dev/null;
sleep 1;
./mgttool.exe -dapollo.c2c.vu7p -q8 -c0 -btx --capture > tracklet_projections_D2PHIB.dat
# D2PHIC
./mgttool.exe -dapollo.c2c.vu7p -q8 -c1 -btx --capture > /dev/null;
sleep 1;
./mgttool.exe -dapollo.c2c.vu7p -q8 -c1 -btx --capture > tracklet_projections_D2PHIC.dat
# D2PHID
./mgttool.exe -dapollo.c2c.vu7p -q8 -c2 -btx --capture > /dev/null;
sleep 1;
./mgttool.exe -dapollo.c2c.vu7p -q8 -c2 -btx --capture > tracklet_projections_D2PHID.dat

# D3PHIB
./mgttool.exe -dapollo.c2c.vu7p -q8 -c3 -btx --capture > /dev/null;
sleep 1;
./mgttool.exe -dapollo.c2c.vu7p -q8 -c3 -btx --capture > tracklet_projections_D3PHIB.dat
# D3PHIC
./mgttool.exe -dapollo.c2c.vu7p -q9 -c0 -btx --capture > /dev/null;
sleep 1;
./mgttool.exe -dapollo.c2c.vu7p -q9 -c0 -btx --capture > tracklet_projections_D3PHIC.dat
# D3PHID
./mgttool.exe -dapollo.c2c.vu7p -q9 -c1 -btx --capture > /dev/null;
sleep 1;
./mgttool.exe -dapollo.c2c.vu7p -q9 -c1 -btx --capture > tracklet_projections_D3PHID.dat

# D4PHIB
./mgttool.exe -dapollo.c2c.vu7p -q9 -c2 -btx --capture > /dev/null;
sleep 1;
./mgttool.exe -dapollo.c2c.vu7p -q9 -c2 -btx --capture > tracklet_projections_D4PHIB.dat
# D4PHIC
./mgttool.exe -dapollo.c2c.vu7p -q9 -c3 -btx --capture > /dev/null;
sleep 1;
./mgttool.exe -dapollo.c2c.vu7p -q9 -c3 -btx --capture > tracklet_projections_D4PHIC.dat
# D4PHID
./mgttool.exe -dapollo.c2c.vu7p -q10 -c0 -btx --capture > /dev/null;
sleep 1;
./mgttool.exe -dapollo.c2c.vu7p -q10 -c0 -btx --capture > tracklet_projections_D4PHID.dat
