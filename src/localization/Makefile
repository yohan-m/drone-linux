.PHONY: clean
.SUFFIXES:

CC = /opt/Codesourcery/bin/arm-none-linux-gnueabi-gcc

all : bddTdoa.o likelyhood.o hyperbolic.o

%o: %c
	$(CC) -c $^ -o $@ 

clean:
	rm -rf *.o
