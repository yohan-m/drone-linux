.PHONY: clean
.SUFFIXES:

CC = /opt/Codesourcery/bin/arm-none-linux-gnueabi-gcc

all : udp_async_driver.o udp_driver_discover.o udp_protocol.o

%o: %c
	$(CC) -c $^ -o $@ 

clean:
	rm -rf *.o
