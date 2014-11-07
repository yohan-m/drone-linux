#include "usb_test.h"

void test_usb_read()
{
	if(usb_driver_init()<0) {
		return;			
	}
	
	unsigned char data[256];
	
	while(1) {
		usb_driver_read(data,256);
	}
	
	usb_driver_close();
}
