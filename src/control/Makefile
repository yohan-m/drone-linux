.PHONY: clean
.SUFFIXES:

CC = /opt/Codesourcery/bin/arm-none-linux-gnueabi-gcc
#CC = gcc

all : control.o controlTask.o mission.o

%o: %c
	$(CC) -c $^ -o $@ 

clean:
	rm -rf *.o
