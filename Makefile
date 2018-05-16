LZ4INC = -Ilz4/lib
ROOTLIBS = $(shell root-config --libs)
CXXFLAGS = $(shell root-config --cflags) -Ilibcpp $(LZ4INC)
LIBFLAG = -c $(shell root-config --auxcflags) $(LZ4INC) -D__LZ4__ -D__LIBZ__
DEBUG = -D__DEBUG__
LIB = $(patsubst %.cpp,%.o,$(wildcard libcpp/*.cpp))
CXX = g++
PROG = hipo2root
LZ4 = lz4/lib/lz4.o

.PHONY: clean
all: $(PROG)

$(LIB): %.o: %.cpp
	$(CXX) $(LIBFLAG) -o $@ $<

$(LZ4):
	make lib -C lz4

test: $(LZ4) $(LIB) all
	$(CXX) -O3 $@.cpp $(LIB) $(LZ4) $(CXXFLAGS) -o test $(ROOTLIBS)

$(PROG): $(LZ4) $(LIB)
	$(CXX) -O3 $@.cpp $(LIB) $(LZ4) $(CXXFLAGS) -o $@ $(ROOTLIBS)

clean:
	-rm -f $(PROG) test
purge: clean
	-rm -f $(HIPOOBJ) $(LIB)
	make clean -C lz4
