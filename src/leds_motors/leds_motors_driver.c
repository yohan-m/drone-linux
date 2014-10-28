#include "leds_motors_driver.h"


int leds_motors_driver_init() 
{
	struct termios config;
	
	//open the device
	leds_motors_device = open(LEDS_MOTORS_DEV, O_RDWR | O_NOCTTY | O_NDELAY);
	if (leds_motors_device < 0) {
		printf("[Error] L%d %s : %s\n",__LINE__,__FUNCTION__,strerror(errno));
		return -1;
	}
	
	//non blocking
	if(fcntl(leds_motors_device, F_SETFL, 0)==-1)   {
		printf("[Error] L%d %s : %s\n",__LINE__,__FUNCTION__,strerror(errno));
		return -2;
	}
	
	//get port config
	if(tcgetattr(leds_motors_device, &config)<0) {
		printf("[Error] L%d %s : %s\n",__LINE__,__FUNCTION__,strerror(errno));
		return -3;
	}

	//set baudrate
	if(cfsetspeed(&config, B115200)<0) {
		printf("[Error] L%d %s : %s\n",__LINE__,__FUNCTION__,strerror(errno));
		return -4;
	}

	config.c_cflag |= (CLOCAL | CREAD); //Enable the receiver and set local mode
	config.c_iflag = 0; //clear input config
	config.c_lflag = 0; //clear local config
	config.c_oflag &= ~OPOST; //clear output config (raw output)
	cfmakeraw(&config); //set mode

	//set port config
	if(tcsetattr(leds_motors_device, TCSANOW, &config)<0) {
		printf("[Error] L%d %s : %s\n",__LINE__,__FUNCTION__,strerror(errno));
		return -5;
	}
	
	if(gpio_set(GPIO_ERROR_RESET, 0)==-1) {
		printf("[Error] L%d %s : gpio_set reset error\n",__LINE__,__FUNCTION__);
		return -6;
	}	
	usleep(100000);
	
	if(gpio_set(GPIO_M1, 0)==-1) {
		printf("[Error] L%d %s : gpio_set m1 error\n",__LINE__,__FUNCTION__);
		return -7;
	}	
	
	if(gpio_set(GPIO_M2, 0)==-1) {
		printf("[Error] L%d %s : gpio_set m2 error\n",__LINE__,__FUNCTION__);
		return -8;
	}	
	
	if(gpio_set(GPIO_M3, 0)==-1) {
		printf("[Error] L%d %s : gpio_set m3 error\n",__LINE__,__FUNCTION__);
		return -9;
	}	
	
	if(gpio_set(GPIO_M4, 0)==-1) {
		printf("[Error] L%d %s : gpio_set m4 error\n",__LINE__,__FUNCTION__);
		return -10;
	}	
	usleep(100000);
	
	int i;
	unsigned char reply[256];
	for (i = 0; i < 4; ++i) {
	
		if(gpio_set(GPIO_M1 + i, -1)==-1) {
			printf("[Error] L%d %s : gpio_set gpio_m1+i i=%d error\n",__LINE__,__FUNCTION__,i);
			return -11;
		}	
		
		usleep(100000);
		
		if(motor_cmd(leds_motors_device, 0xE0, reply, 2)<0) {
			printf("[Error] L%d %s : motor_cmd e0 i=%d error\n",__LINE__,__FUNCTION__,i);
			return -12;
		}	
		
		if(motor_cmd(leds_motors_device, 0x91, reply, 121)<0) {
			printf("[Error] L%d %s : motor_cmd 91 i=%d error\n",__LINE__,__FUNCTION__,i);
			return -13;
		}	
		
		if(motor_cmd(leds_motors_device, 0xA1, reply, 2)<0) {
			printf("[Error] L%d %s : motor_cmd a1 i=%d error\n",__LINE__,__FUNCTION__,i);
			return -14;
		}	
		
		if(motor_cmd(leds_motors_device, i + 1, reply, 1)<0) {
			printf("[Error] L%d %s : motor_cmd i+1 i=%d error\n",__LINE__,__FUNCTION__,i);
			return -15;
		}	
		
		if(motor_cmd(leds_motors_device, 0x40, reply, 2)<0) {
			printf("[Error] L%d %s : motor_cmd 40 i=%d error\n",__LINE__,__FUNCTION__,i);
			return -16;
		}	
		
		if(gpio_set(GPIO_M1 + i ,0)<0) {
			printf("[Error] L%d %s : gpio_set gpio_m1+i i=%d error\n",__LINE__,__FUNCTION__,i);
			return -17;
		}	
		
		usleep(100000);
	}
	
	if(gpio_set(GPIO_M1, -1)==-1) {
		printf("[Error] L%d %s : gpio_set gpio_m1 error\n",__LINE__,__FUNCTION__);
		return -18;
	}	
	
	if(gpio_set(GPIO_M2, -1)==-1) {
		printf("[Error] L%d %s : gpio_set gpio_m2 error\n",__LINE__,__FUNCTION__);
		return -19;
	}	
	
	if(gpio_set(GPIO_M3, -1)==-1) {
		printf("[Error] L%d %s : gpio_set gpio_m3 error\n",__LINE__,__FUNCTION__);
		return -20;
	}	
	
	if(gpio_set(GPIO_M4, -1)==-1) {
		printf("[Error] L%d %s : gpio_set gpio_m4 error\n",__LINE__,__FUNCTION__);
		return -21;
	}	
	
	usleep(100000);

	if(gpio_set(GPIO_ERROR_READ, -1)==-1) {
		printf("[Error] L%d %s : gpio_set gpio_m2 error\n",__LINE__,__FUNCTION__);
		return -22;
	}		
	usleep(100000);

	#ifdef DEBUG
		printf("[Debug] L%d %s : Ok\n",__LINE__,__FUNCTION__);		
	#endif
	
	return 0;
}


int leds_motors_driver_close()
{
	if(close(leds_motors_device)<0) {
		printf("[Error] L%d %s : %s\n",__LINE__,__FUNCTION__,strerror(errno));
		return -1;
	}
	
	#ifdef DEBUG
		printf("[Debug] L%d %s : Ok\n",__LINE__,__FUNCTION__);		
	#endif
	
	return 0;
}


int leds_motors_driver_write(unsigned char * data, int size) 
{
	int cnt_bytes = write(leds_motors_device, data, size);

	if(cnt_bytes < 0) {
		printf("[Error] L%d %s : %s\n",__LINE__,__FUNCTION__,strerror(errno));
		return -1;
	}

	#ifdef DEBUG
		printf("[Debug] L%d %s : %d bytes : ",__LINE__,__FUNCTION__,size);	
		int i;
		for(i=0 ; i<cnt_bytes ; i++) {
			printf("0x%X ",data[i]);
		}
		printf("\n");
	#endif
	
	return cnt_bytes;
}


int gpio_set (int nr, int val)  {
	char cmdline[200];

	if (val < 0)
		sprintf(cmdline, "/usr/sbin/gpio %d -d i", nr);
	else if (val > 0)
		sprintf(cmdline, "/usr/sbin/gpio %d -d ho 1", nr);
	else
		sprintf(cmdline, "/usr/sbin/gpio %d -d ho 0", nr);

	return system(cmdline);
}


int motor_cmd(int file, unsigned char cmd, unsigned char *reply, int replylen) {
	int size;

	write(file, &cmd, 1);
	fsync(file);
	usleep(50000);
	size = read(file, reply, replylen);

	return size;
}
