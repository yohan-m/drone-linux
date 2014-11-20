#!/bin/sh

make
make clean

ftp -v "192.168.1.1" <<END_SCRIPT
lcd ./
put ardrone_localization
exit
END_SCRIPT

telnet "192.168.1.1"
