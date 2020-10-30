#!/bin/sh

bx=$1

quads=(1 2 3 4 13 15 16 17);
chans=(0 1 2 3);
for q in ${quads[*]}; do
    for c in ${chans[*]}; do
	offset_i=`./mgttool.exe -dapollo.c2c.vu7p -q$q -c$c --capture | grep 1000 | awk '{print $2}'`
	delta=`echo "($bx-${offset_i})/4" | bc` 
	echo "quad: $q channel: $c offset: ${offset_i} delta: $delta"
	
	if (( `echo "${delta} != 0" | bc` )); then
	    echo "aligning ..." 
	    ./mgttool.exe -dapollo.c2c.vu7p -q$q -c$c -a${delta} 
	fi;
    done
done
