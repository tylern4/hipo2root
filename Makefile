ROOTLIBS	= $(shell root-config --libs)
HIPOLIBS = -Llibcpp -lhipo
HIPOINC = -Ilibcpp
HIPOOBJ = libcpp/libhipo.o

CXX = g++
CXXFLAGS = -O2 -fPIC -w -g $(shell root-config --cflags) $(HIPOINC)
TARGET =	hipo2root
FILENAME =	hipo2root

all:	clean libcpp main

libcpp:
	scons

main:	$(FILENAME).o
	$(CXX) $(FILENAME).o $(HIPOOBJ) -L. $(CXXFLAGS)  $(ROOTLIBS) -o $(TARGET)

clean:
	-rm -f $(TARGET) $(FILENAME).o
