#!/bin/sh

count=0;
#for d in `ls -1d TEtestfiles/*`; do
for d in `ls -1d newdata/TE*`; do
    echo "count: $count dir: $d"
    ls $d
    inner=`ls $d/VMStubs_VMSTE_L1PHI*.dat`; 
    outer=`ls $d/VMStubs_VMSTE_L2PHI*.dat`;
    echo "inner: $inner"
    echo "outer: $outer"
    memfile="memfile_TE_${count}.dat"
    echo "memfile: $memfile"
    ./buffer_gen_TE.exe ${inner} ${outer} ${memfile}
    echo ""
    ln -s $d dir_${count};
    sp=`ls $d/Stub*.dat`;
    cp $sp sp_${count}.dat;

    (( count++ ));

done;
