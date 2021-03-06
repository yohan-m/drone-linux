#include "udp_manager_test.h"

void test_udp_manager()
{
	int cnt = 0;
	char c;
	int fd;
	
	wifiFrame frame = createWifiFrame(TIME_FRAME, 123456789, 2974674, 48486);
	char * data;
	data = wifiFrameToChar(frame);
	
	
	udp_async_driver_init(31000,52400,"192.168.1.3",&fd);
	udp_async_driver_enable_read(&test_callback_receive_manager,64,fd);
	
	while(cnt <20) { 
		printf("press s to send data\n");
		c = getchar();	
		if(c=='s') {
			udp_async_driver_write((unsigned char *)data,19,fd);
		}	
		cnt++;
	}
	
	udp_async_driver_close(fd);
}

void test_callback_receive_manager(unsigned char * data, int size)
{
	if(size==19) {
		wifiFrame frame = wifiFrameFromChar((char *)data);		
		printf("[Test] L%d %s : seqNum%d type=%c data0=%d data1=%d data2=%d data3=%d\n",__LINE__,__FUNCTION__,frame.seqNum,frame.type,frame.positions[0],frame.positions[1],frame.positions[2]);	
	}
	else {
		printf("[Test] L%d %s : (%d bytes) Unknow frame %s\n",__LINE__,__FUNCTION__,size,data);		
	}
}
