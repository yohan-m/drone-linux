.PHONY: clean
.SUFFIXES:

CC = /opt/Codesourcery/bin/arm-none-linux-gnueabi-gcc

all : navdataLocal.o navdataToPC.o struct.h

%o: %c
	$(CC) -c $^ -o $@ 

clean:
	rm -rf *.o
