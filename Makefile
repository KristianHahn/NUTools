ZYNQROOT=/mnt/zynq_root
BOOSTDIR=/scratch/boost_cxx
PLNXDIR=/scratch/petalinux-v2017.2

CXX=arm-linux-gnueabihf-c++ 
CXXFLAGS=--sysroot=${ZYNQROOT} -isystem ${ZYNQROOT} -g -O2 -std=c++11 -Wall -Wno-format-zero-length -fPIC -DDISABLE_PACKET_COUNTER_HACK 

INCLUDE_DIRS=/scratch/petalinux-v2017.2/tools/linux-i386/gcc-arm-linux-gnueabi/arm-linux-gnueabihf/libc/usr/include/ /scratch/petalinux-v2017.2/tools/linux-i386/gcc-arm-linux-gnueabi/arm-linux-gnueabihf/libc/usr/include/ ${BOOSTDIR}/include/   ipbus-software/uhal/uhal/include/  ipbus-software/uhal/grammars/include/ ipbus-software/uhal/log/include/
LIB_DIRS=${ZYNQROOT}/lib ${BOOSTDIR}/lib ipbus-software/uhal/uhal/lib/ ipbus-software/extern/pugixml/pugixml-1.2  ipbus-software/uhal/grammars/lib/  ipbus-software/uhal/log/lib/ ipbus-software/uhal/uhal/lib/ ipbus-software/uhal/tests/lib/  
LIBS=cactus_uhal_uhal boost_filesystem pugixml cactus_uhal_grammars cactus_uhal_log cactus_uhal_uhal  cactus_uhal_tests boost_unit_test_framework boost_system boost_thread boost_chrono boost_regex boost_program_options boost_timer c_nonshared

INCLUDE_FLAGS=$(foreach d, $(INCLUDE_DIRS), -I$d) 
LD_FLAGS=$(foreach d, $(LIB_DIRS), -L$d) $(foreach f, $(LIBS), -l$f)


all : mgt reg

mgt : mgttool.exe
mgttool.exe : mgtargs.o mgtroutines.o

reg : regtool.exe
regtool.exe : regargs.o


%.o : %.cc
	export PATH=/scratch/python2.7/bin:/scratch/tar_1_24/bin:/scratch/socat_2_0_0/bin:${PATH}; \
	export PYTHONPATH=/scratch/python2.7/lib; \
	source ${PLNXDIR}/settings.sh; \
	$(CXX) $(CXX_FLAGS) $(INCLUDE_FLAGS) -c $< -o $@

%.exe : *.o %.cc
	export PATH=/scratch/python2.7/bin:/scratch/tar_1_24/bin:/scratch/socat_2_0_0/bin:${PATH}; \
	export PYTHONPATH=/scratch/python2.7/lib; \
	source ${PLNXDIR}/settings.sh; \
	$(CXX) $(CXX_FLAGS) $(INCLUDE_FLAGS)  $^ -o $@ $(LD_FLAGS)




