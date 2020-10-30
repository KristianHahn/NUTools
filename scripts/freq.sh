#!/bin/sh

count=`echo $1 | sed -e 's,0x,,' | tr '[:lower:]' '[:upper:]'`
var=`echo "ibase=16; $count" | bc`
f=`echo "$var*119.20928 / 1000000;" | bc -l `
echo "$f MHz"

 
