#include "udp_manager_test.h"

void test_udp_manager()
{
	int cnt = 0;
	char c;
	
	wifiFrame frame = createWifiFrame(TIME_FRAME, 123456789, 2974674, 48486, 256155);
	char data[19];
	wifiFrameToChar(frame, data);
	
	udp_async_driver_init(31000,52400,"192.168.1.3");
	udp_async_driver_enable_read(&test_callback_receive_manager,64);
	
	while(cnt <20) { 
		printf("press s to send data\n");
		c = getchar();	
		if(c=='s') {
			udp_async_driver_write((unsigned char *)data,19);
		}	
		cnt++;
	}
	
	udp_async_driver_close();
}

void test_callback_receive_manager(unsigned char * data, int size)
{
	if(size==19) {
		wifiFrame frame = wifiFrameFromChar((char *)data);		
		printf("[Test] L%d %s : seqNum = %d\n",__LINE__,__FUNCTION__,frame.seqNum);	
		printf("[Test] L%d %s : type   = %c\n",__LINE__,__FUNCTION__,frame.type);	
		printf("[Test] L%d %s : data0  = %d\n",__LINE__,__FUNCTION__,frame.data[0]);
		printf("[Test] L%d %s : data1  = %d\n",__LINE__,__FUNCTION__,frame.data[1]);
		printf("[Test] L%d %s : data2  = %d\n",__LINE__,__FUNCTION__,frame.data[2]);
		printf("[Test] L%d %s : data3  = %d\n",__LINE__,__FUNCTION__,frame.data[3]);	
	}
	else {
		printf("[Test] L%d %s : (%d bytes) Unknow frame %s\n",__LINE__,__FUNCTION__,size,data);		
	}
}
