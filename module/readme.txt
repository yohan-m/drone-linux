USB Linux Module


	I. Check the version of the drone
Connect your computer to the drone and open a terminal :
# telnet 192.168.1.1
# uname -a
This command gives you the version of the kernel that runs on the drone.
If the version is 2.6.32.9-g980dab2, please go to the part V. The file cdc-acm.ko is already compilated for this version.


	II. Download
Download linux.tar.gz here : https://devzone.parrot.com/projects/list_files/oss-ardrone2


	III. Config the kernel
In the linux folder previously downloaded, modify the Makefile :
At the beginning of the file, there is a line like "EXTRAVERSION = .9". Modify this line with your kernel version.
For example, if the your version is "2.6.32.9-g0d605ac", put "EXTRAVERSION = .9-g0d605ac".
Open a terminal in the linux folder previously downloaded :
# cp kernel.config .config
# make ARCH=arm menuconfig
Navigate through the menuconfig : Device drivers > USB support
Press "space" on "USB Modem (CDC ACM) support" to set it as a module (M).
Close and save the config.


	IV. Compile the module
Open a terminal in the linux folder :
# make ARCH=arm CROSS_COMPILE=/path/to/the/crosscompiler/bin/arm-none-linux-gnueabi- modules


	V. Install le module
In the folder linux/drivers/usb/class there should be a cdc-acm.ko file.
Open a terminal in this folder :
# ftp 192.168.1.1
# put cdc-acm.ko
# exit
# telnet 192.168.1.1
# mkdir /lib/modules/<version>/kernel/drivers/cdc-acm
# cd data/video
# cp cdc-acm.ko /lib/modules/<version>/kernel/drivers/cdc-acm/cdc-acm.ko
# cd /lib/modules/<version>/kernel/drivers/cdc-acm/
# insmod cdc_acm.ko
You can check that the module was correctly loaded with :
# lsmod


	VI. Permanent module
If you reboot the drone, the module will be unloaded and you have to execute insmod again.
There is a way to automatically load the module at the boot. Open a terminal :
# telnet 192.168.1.1
# vi /etc/init.d/rcS
Edit the rcS file, at the end of the file add this line :
insmod /lib/modules/<version>/kernel/drivers/cdc-acm/cdc-acm.ko

	
