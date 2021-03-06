#include "usb_async_test.h"

void test_usb_async()
{
	if(usb_async_driver_init()<0) {
		return;
	}
	
	if(usb_async_driver_enable_read(&test_callback_receive_usb,256)<0) {
		return;
	}
	
	while(1) { 
		usleep(500);
	}
	
	usb_async_driver_close();
}

void test_callback_receive_usb(unsigned char * data, int size)
{
	printf("[Test] L%d %s : (%d bytes) %s\n",__LINE__,__FUNCTION__,size,data);	
}
