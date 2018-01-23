ROOTLIBS	= $(shell root-config --libs)
HIPOLIBS = -Llibcpp -lhipo
HIPOINC = -Ilibcpp
HIPOOBJ = libcpp/libhipo.o
LIBFLAG = -c -O2 -fPIC -m64 -fmessage-length=0 -g -D__LZ4__ -D__LIBZ__
LIB = $(patsubst %.cpp,%.o,$(wildcard libcpp/*.cpp))


CXX = g++
CXXFLAGS = -O2 -fPIC -w -g $(shell root-config --cflags) $(HIPOINC)
TARGET =	hipo2root
FILENAME =	hipo2root

all:	clean hipo main

hipo: $(LIB)
	ar rc $(HIPOOBJ) $(LIB)

$(LIB): %.o: %.cpp
	$(CXX) $(LIBFLAG) -o $@ $<

main:	$(FILENAME).o
	$(CXX) $(FILENAME).o $(HIPOOBJ) -L. $(CXXFLAGS) -o $(TARGET) $(ROOTLIBS)

clean:
	-rm -f $(TARGET) $(FILENAME).o $(HIPOOBJ) $(LIB)
