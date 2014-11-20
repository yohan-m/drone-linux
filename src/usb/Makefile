.PHONY: clean
.SUFFIXES:

CC = /opt/Codesourcery/bin/arm-none-linux-gnueabi-gcc

all : usb_driver.o usb_protocol_sync.o

%o: %c
	$(CC) -c $^ -o $@ 
clean:
	rm -rf *.o
