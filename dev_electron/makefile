INCDIR = $(QpixDir)/include
LIBDIR = $(QpixDir)/Library

# Compiler flags
CFLAGS = -Wall -Wextra -Wno-long-long \
	-O3 -fno-common -c \
	-I$(INCDIR)

LDFLAGS = -L$(LIBDIR) -lQpix

test: energy_to_electron.cc 
	$(CXX) $(CFLAGS) energy_to_electron.cc
	$(CXX)  -o energy_to_electron energy_to_electron.o $(LDFLAGS)
	rm energy_to_electron.o

