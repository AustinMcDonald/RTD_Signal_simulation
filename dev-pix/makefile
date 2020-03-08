INCDIR = $(QpixDir)/include
LIBDIR = $(QpixDir)/Library

# Compiler flags
CFLAGS = -std=c++11 -Wall -Wextra -Wno-long-long \
	-O3 -fno-common -c \
	-I$(INCDIR)

LDFLAGS = -L$(LIBDIR) -lQpix

test: dev-pix.cc 
	$(CXX) $(CFLAGS) dev-pix.cc
	$(CXX)  -o dev-pix dev-pix.o $(LDFLAGS)
	rm dev-pix.o

