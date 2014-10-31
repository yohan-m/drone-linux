#include "usb_test.h"

void test_usb_read()
{
	if(usb_driver_init()<0) {
		return;			
	}
	
	unsigned char data[64];
	
	usb_driver_read(data,64);
	usb_driver_read(data,64);
	usb_driver_read(data,64);
	usb_driver_read(data,64);
	
	usb_driver_close();
}
