#!/bin/sh

ftp -v -n 192.168.1.1 <<END_SCRIPT
lcd ./
put ardrone_localization
exit
END_SCRIPT
exit 0

