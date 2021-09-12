#!/bin/sh 


if (( $# != 1 )); then 
    echo "arguments: " 
    echo "   1 - resets eth, disables payload"
    echo "   0 - cleares eth reset , enables payload"
elif (( $1 == 1 )); then
    echo "resetting"
    regtool.exe -dx0 -rpayload.ctrl.reg.en 0
    regtool.exe -dx0 -reth10g.ctrl.reg.rst 1
elif (( $1 == 0 )); then
    echo "clearing reset"
    regtool.exe -dx0 -rpayload.ctrl.reg.en 1
    regtool.exe -dx0 -reth10g.ctrl.reg.rst 0
else 
    echo "arguments: " 
    echo "   1 - resets eth, disables payload"
    echo "   0 - cleares eth reset , enables payload"
fi;
