.PHONY: 
.SUFFIXES:
 
CC = /opt/Codesourcery/bin/arm-none-linux-gnueabi-gcc
OBJ = ./../../common-sources/src/*.o ../src/main.o  ../src/localization/*.o ../src/udp/*.o ../src/usb/*.o ../src/demo/*.o ../src/navdata/*.o  ../src/control/*.o 
 
all:	$(OBJ)
	$(CC) $(OBJ) -pthread -lm -lpthread -o ardrone_localization
 
%.o: 
	$(CC) -c ../src/main.c -o ../src/main.o
	$(MAKE) -C ./../../common-sources/src
	$(MAKE) -C ../src/localization
	$(MAKE) -C ../src/udp
	$(MAKE) -C ../src/usb
	$(MAKE) -C ../src/demo
	$(MAKE) -C ../src/navdata
	$(MAKE) -C ../src/control

clean:
	rm -rf ../src/main.o
	$(MAKE) -C ../../common-sources/src clean
	$(MAKE) -C ../src/localization clean
	$(MAKE) -C ../src/udp clean
	$(MAKE) -C ../src/usb clean
	$(MAKE) -C ../src/demo clean
	$(MAKE) -C ../src/navdata clean
	$(MAKE) -C ../src/control clean




