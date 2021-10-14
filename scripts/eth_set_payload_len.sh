#
# for bandwidth scanning from PC
#

#!/bin/sh

size_in_dec=$1
size_in_hex=`echo "obase=16; ${size_in_dec}" | bc`;


source ./scripts/env.sh
export NU_TOOLS_XML=file:///${PKGDIR}/addrtab


# disable payload generation
regtool.exe -dx0 -rpayload.ctrl.reg.en 0

# disable the link
regtool.exe -dx0 -reth10g.ctrl.reg.rst  1

# configue the payload generator
regtool.exe -dx0 -rpayload.ctrl.pkt_len 0x${size_in_hex}

# let rate drop to zero
sleep 6

# reenable the link 
regtool.exe -dx0 -reth10g.ctrl.reg.rst  0

# enable payload generation
regtool.exe -dx0 -rpayload.ctrl.reg.en 1
