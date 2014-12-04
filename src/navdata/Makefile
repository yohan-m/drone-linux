.PHONY: clean
.SUFFIXES:

CC = /opt/Codesourcery/bin/arm-none-linux-gnueabi-gcc

all : navdataLocal.o navdataToPC.o navdata_manager.o struct.h

%o: %c
	$(CC) -pthread -lpthread -c $^ -o $@ 

clean:
	rm -rf *.o
