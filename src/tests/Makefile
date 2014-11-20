.PHONY: clean
.SUFFIXES:

CC = /opt/Codesourcery/bin/arm-none-linux-gnueabi-gcc

all : udp_async_test.o udp_disco_test.o udp_manager_test.o udp_protocol_test.o usb_protocol_test.o usb_test.o

%o: %c
	$(CC) -c $^ -o $@ 
clean:
	rm -rf *.o
