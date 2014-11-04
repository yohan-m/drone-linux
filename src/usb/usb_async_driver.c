#include "usb_async_driver.h"


int usb_async_driver_init()
{
	struct termios config;
	
	//open the device
	usb_async_device = open(USB_ASYNC_DEV, O_RDWR | O_NOCTTY | O_SYNC);
	if (usb_async_device < 0) {
		printf("[Error] L%d %s : %s\n",__LINE__,__FUNCTION__,strerror(errno));
		return -1;
	}
	
	//get port config
	if(tcgetattr(usb_async_device, &config)<0) {
		printf("[Error] L%d %s : %s\n",__LINE__,__FUNCTION__,strerror(errno));
		return -3;
	}

	//set baudrate
	/*if(cfsetspeed(&config, B9600)<0) {
		printf("[Error] L%d %s : %s\n",__LINE__,__FUNCTION__,strerror(errno));
		return -4;
	}*/

	config.c_cflag |= (CLOCAL | CREAD); //Enable the receiver and set local mode
	config.c_iflag = 0; //clear input config
	config.c_lflag = 0; //clear local config
	config.c_oflag &= ~OPOST; //clear output config (raw output)
	cfmakeraw(&config); //set mode

	//set port config
	if(tcsetattr(usb_async_device, TCSANOW, &config)<0) {
		printf("[Error] L%d %s : %s\n",__LINE__,__FUNCTION__,strerror(errno));
		return -5;
	}
		
	#ifdef DEBUG
		printf("[Debug] L%d %s : Ok\n",__LINE__,__FUNCTION__);		
	#endif

	return 0;
}


int usb_async_driver_close()
{
	if(close(usb_async_device)<0) {
		printf("[Error] L%d %s : %s\n",__LINE__,__FUNCTION__,strerror(errno));
		return -1;
	}
	
	#ifdef DEBUG
		printf("[Debug] L%d %s : Ok\n",__LINE__,__FUNCTION__);		
	#endif
	
	return 0;
}


int usb_async_driver_enable_read(usb_function callback_receive_fct, int packet_size)
{
	int flags;
	struct sigaction sa;
	
	//get global variable for the handler
	usb_packet_size = packet_size;
	callback_receive_usb = callback_receive_fct;

	//add ASYNC flags to the socket
	flags = fcntl(usb_async_device, F_GETFL);
	if(fcntl(usb_async_device, F_SETFL, flags | O_ASYNC)<0) {
		printf("[Error] L%d %s : %s\n",__LINE__,__FUNCTION__,strerror(errno));
		return -1;
	}
		
	//configure the sigaction structure
	sa.sa_flags = 0;
	sa.sa_handler = usb_async_driver_handler;
	sigemptyset(&sa.sa_mask);

	//get the signal
	if (sigaction(SIGIO, &sa, NULL)<0) {
		printf("[Error] L%d %s : %s\n",__LINE__,__FUNCTION__,strerror(errno));
		return -2;	
	}

	//indicate this pid will receive the signal
	if (fcntl(usb_async_device, F_SETOWN, getpid())<0) {
		printf("[Error] L%d %s : %s\n",__LINE__,__FUNCTION__,strerror(errno));
		return -3;	
	}

	//set the signal sent
	if (fcntl(usb_async_device, F_SETSIG, SIGIO)<0) {
		printf("[Error] L%d %s : %s\n",__LINE__,__FUNCTION__,strerror(errno));
		return -4;	
	}
    
	#ifdef DEBUG
		printf("[Debug] L%d %s : Ok\n",__LINE__,__FUNCTION__);		
	#endif

	return 0;
}


void usb_async_driver_handler(int sig)
{
	unsigned char data[usb_packet_size];
	int cnt_bytes = read(usb_async_device, data, usb_packet_size);

	if(cnt_bytes<0) {
		printf("[Error] L%d %s : %s\n",__LINE__,__FUNCTION__,strerror(errno));
		return;
	}

	#ifdef DEBUG
		printf("[Debug] L%d %s : %d bytes : ",__LINE__,__FUNCTION__,cnt_bytes);	
		int i;
		for(i=0 ; i<cnt_bytes ; i++) {
			printf("0x%X ",data[i]);
		}
		printf("(%s)\n",data);
	#endif
	
	callback_receive_usb(data,cnt_bytes);
}
