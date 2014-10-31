#!/bin/sh

ftp -v "192.168.1.1" <<END_SCRIPT
lcd ./
put ardrone_localization
exit
END_SCRIPT
exit 0

