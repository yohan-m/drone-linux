#!/bin/sh

cd ../src/localization

ftp -v "192.168.1.1" <<END_SCRIPT

put tdoa1-2.txt
put tdoa1-3.txt
put tdoa1-4.txt
put tdoa2-1.txt
put tdoa2-3.txt
put tdoa2-4.txt
put tdoa3-1.txt
put tdoa3-2.txt
put tdoa3-4.txt
put tdoa4-1.txt
put tdoa4-2.txt
put tdoa4-3.txt

END_SCRIPT
