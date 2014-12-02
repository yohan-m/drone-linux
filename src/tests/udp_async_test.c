#include "udp_async_test.h"

void test_udp_async()
{
	int cnt = 0;
	unsigned char data[5];
	data[0]='t';
	data[1]='e';
	data[2]='s';
	data[3]='t';
	data[4]='\0';
	
	char c;
	int fd;
	
	udp_async_driver_init(30000,31000,"192.168.1.4",&fd);
	udp_async_driver_enable_read(&test_callback_receive,64,fd);
	
	while(cnt <10) { 
		printf("getchar() ?\n");
		c = getchar();	
		if(c=='s') {
			udp_async_driver_write(data,5,fd);
		}	
		cnt++;
	}
	
	udp_async_driver_close(fd);
}

void test_callback_receive(unsigned char * data, int size)
{
	printf("[Test] L%d %s : (%d bytes) %s\n",__LINE__,__FUNCTION__,size,data);	
}
