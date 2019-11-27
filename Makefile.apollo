CXX=g++
CXXFLAGS=-g -O2 -std=c++11 -Wall -Wno-format-zero-length -fPIC -DDISABLE_PACKET_COUNTER_HACK 

INCLUDE_DIRS=/usr/include /work/include/   /work/include/uhal/uhal/include/  /work/include/uhal/grammars/include/ /work/include/uhal/log/include/
LIB_DIRS=/usr/lib /work/lib   
LIBS=cactus_uhal_uhal boost_filesystem pugixml cactus_uhal_grammars cactus_uhal_log cactus_uhal_uhal boost_unit_test_framework boost_system boost_thread boost_chrono boost_regex boost_program_options boost_timer c_nonshared

INCLUDE_FLAGS=$(foreach d, $(INCLUDE_DIRS), -I$d) 
LD_FLAGS=$(foreach d, $(LIB_DIRS), -L$d) $(foreach f, $(LIBS), -l$f)


all : mgt reg payload ttc

mgt : mgttool.exe
mgttool.exe : mgtargs.o mgtroutines.o

payload : payloadtool.exe
payloadtool.exe : mgtargs.o mgtroutines.o

reg : regtool.exe
regtool.exe : regargs.o


ttc : ttctool.exe
ttctool.exe : ttcargs.o ttcroutines.o

%.o : %.cc
	$(CXX) $(CXX_FLAGS) $(INCLUDE_FLAGS) -c $< -o $@

%.exe : %.cc
	$(CXX) $(CXX_FLAGS) $(INCLUDE_FLAGS)  $^ -o $@ $(LD_FLAGS)

clean :
	rm *.o *.exe
