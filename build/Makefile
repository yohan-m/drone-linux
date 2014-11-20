.PHONY: 
.SUFFIXES:
 
CC = /opt/Codesourcery/bin/arm-none-linux-gnueabi-gcc
OBJ = ./../../common-sources/src/*.o ../src/main.o  ../src/localization/*.o ../src/udp/*.o ../src/usb/*.o ../src/tests/*.o ../src/demo/*.o 
 
all:	$(OBJ)
	$(CC) $(OBJ) -lm -o ardrone_localization
 
%.o: 
	$(CC) -c ../src/main.c -o ../src/main.o
	$(MAKE) -C ./../../common-sources/src
	$(MAKE) -C ../src/localization
	$(MAKE) -C ../src/udp
	$(MAKE) -C ../src/usb
	$(MAKE) -C ../src/tests
	$(MAKE) -C ../src/demo

clean:
	rm -rf ../src/main.o
	$(MAKE) -C ../../common-sources/src clean
	$(MAKE) -C ../src/localization clean
	$(MAKE) -C ../src/udp clean
	$(MAKE) -C ../src/usb clean
	$(MAKE) -C ../src/tests clean
	$(MAKE) -C ../src/demo clean




