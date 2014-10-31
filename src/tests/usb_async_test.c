#include "usb_async_test.h"

void test_usb_async()
{
	int cnt = 0;
	unsigned char data[5];
	data[0]='t';
	data[1]='e';
	data[2]='s';
	data[3]='t';
	data[4]='\0';
	
	char c;
	
	usb_async_driver_init();
	usb_async_driver_enable_read(&test_callback_receive_usb,64);
	
	while(cnt <10) { 
		printf("getchar() ?\n");
		c = getchar();	
		if(c=='s') {
			usb_async_driver_write(data,5);
		}	
		cnt++;
	}
	
	usb_async_driver_close();
}

void test_callback_receive_usb(unsigned char * data, int size)
{
	printf("[Test] L%d %s : (%d bytes) %s\n",__LINE__,__FUNCTION__,size,data);	
}
