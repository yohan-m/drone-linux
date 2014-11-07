#include "usb_driver.h"

int usb_driver_init()
{
	struct termios config;
	
	//open the device
	usb_device = open(USB_DEV, O_RDWR | O_NOCTTY| O_SYNC);
	if (usb_device < 0) {
		printf("[Error] L%d %s : %s\n",__LINE__,__FUNCTION__,strerror(errno));
		return -1;
	}
	
	//get port config
	if(tcgetattr(usb_device, &config)<0) {
		printf("[Error] L%d %s : %s\n",__LINE__,__FUNCTION__,strerror(errno));
		return -2;
	}
	
	//set baudrate
	/*if(cfsetspeed(&config, B57600)<0) {
		printf("[Error] L%d %s : %s\n",__LINE__,__FUNCTION__,strerror(errno));
		return -3;
	}*/
	
	config.c_cflag |= (CLOCAL | CREAD); //Enable the receiver and set local mode
	config.c_iflag = 0; //clear input config
	config.c_lflag = 0; //clear local config
	config.c_oflag &= ~OPOST; //clear output config (raw output)
	cfmakeraw(&config); //set mode

	//set port config
	if(tcsetattr(usb_device, TCSANOW, &config)<0) {
		printf("[Error] L%d %s : %s\n",__LINE__,__FUNCTION__,strerror(errno));
		return -4;
	}

	return 0;
}


int usb_driver_close()
{
	if(close(usb_device)<0) {
		printf("[Error] L%d %s : %s\n",__LINE__,__FUNCTION__,strerror(errno));
		return -1;
	}
	
	return 0;
}


int usb_driver_read(unsigned char * data, int size)
{
	int cnt_bytes = read(usb_device, data, size);

	if(cnt_bytes<0) {
		printf("[Error] L%d %s : %s\n",__LINE__,__FUNCTION__,strerror(errno));
		return -1;
	}

	#ifdef DEBUG_USB_DRIVER
		printf("[Debug] L%d %s : %d bytes : ",__LINE__,__FUNCTION__,cnt_bytes);	
		int i;
		for(i=0 ; i<cnt_bytes ; i++) {
			printf("0x%X ",data[i]);
		}
		printf("(%s)\n",data);
	#endif
	
	return cnt_bytes;
}
