ROOTLIBS	= $(shell root-config --libs)
HIPOLIBS = -Llibcpp -lhipo
HIPOINC = -Ilibcpp
HIPOOBJ = libcpp/libhipo.o
LIBFLAG = -c -O2 -fPIC -m64 -fmessage-length=0 -g -D__LZ4__ -D__LIBZ__
LIB = $(patsubst %.cpp,%.o,$(wildcard libcpp/*.cpp))
CXX = g++
CXXFLAGS = -O2 -fPIC -w -g $(shell root-config --cflags) $(HIPOINC)
PROG =	hipo2root

.PHONY: clean

all: $(PROG)

$(LIB): %.o: %.cpp
	$(CXX) $(LIBFLAG) -o $@ $<

$(PROG): $(LIB)
	$(CXX) $@.cpp $(LIB) $(CXXFLAGS) -o $@ $(ROOTLIBS)

clean:
	-rm -f $(PROG) $(HIPOOBJ) $(LIB)
