#include "usb_driver.h"

int usb_driver_init()
{
	struct termios config;
	
	//find the device
	char name[64];
	memcpy(name,"/dev/",5);
	if (usb_driver_find_dev(&name[5])<0) {
		return -1;
	}
	
	#ifdef DEBUG_INFO
		printf("[Debug] L%d %s : USB device found %s\n",__LINE__,__FUNCTION__,name);	
	#endif
	
	//open the device
	usb_device = open(name, O_RDWR | O_NOCTTY| O_SYNC);
	if (usb_device < 0) {
		printf("[Error] L%d %s : %s\n",__LINE__,__FUNCTION__,strerror(errno));
		return -2;
	}
	
	//get port config
	if(tcgetattr(usb_device, &config)<0) {
		printf("[Error] L%d %s : %s\n",__LINE__,__FUNCTION__,strerror(errno));
		return -3;
	}
	
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


int usb_driver_find_dev(char * name)
{
   	DIR * d;
    struct dirent *dir;
    int found = 0;

    d = opendir ("/dev/");

    if (!d) {
		printf("[Error] L%d %s : %s\n",__LINE__,__FUNCTION__,strerror(errno));
        return -1;
    }
    
    while ((dir = readdir(d)) != NULL && found==0)
    {
      	//printf("%s %d\n", dir->d_name, sizeof(dir->d_name));
      	if(memcmp(dir->d_name,"ttyACM",6)==0) {
    		found = 1;
      		memcpy(name,dir->d_name,16);
      	}
    }
    
    if (closedir (d)) {
		printf("[Error] L%d %s : %s\n",__LINE__,__FUNCTION__,strerror(errno));
        return -2;
    }
    
    if(found == 0) {
		printf("[Error] L%d %s : USB device not found\n",__LINE__,__FUNCTION__);
        return -3;    	
    }

	return 0;
}



