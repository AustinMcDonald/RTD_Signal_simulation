INCDIR = $(QpixDir)/include
LIBDIR = $(QpixDir)/Library

# Compiler flags
CFLAGS = -std=c++11 -Wall -Wextra -Wno-long-long \
	-O3 -fno-common -c \
	-I$(INCDIR)

LDFLAGS = -L$(LIBDIR) -lQpix
#LDFLAGS += `root-config --glibs`

test: readAr39.cc 
	$(CXX) $(CFLAGS) readAr39.cc
	$(CXX)  -o readAr39 readAr39.o $(LDFLAGS)
	rm readAr39.o

