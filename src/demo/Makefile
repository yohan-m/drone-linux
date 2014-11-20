.PHONY: clean
.SUFFIXES:

CC = /opt/Codesourcery/bin/arm-none-linux-gnueabi-gcc

all : com_demo.o 

%o: %c
	$(CC) -c $^ -o $@ 
clean:
	rm -rf *.o
