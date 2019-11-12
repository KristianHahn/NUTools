#!/bin/sh

bx=$1

quads=(1 2 3 4 13 15 16 17);
for q in ${quads[*]}; do
    ./mgttool.exe -dapollo.c2c.vu7p -q$q -r -v 
done
