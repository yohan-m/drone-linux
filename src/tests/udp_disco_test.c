#include "udp_disco_test.h"

void test_udp_disco()
{
	char IP[IP_SIZE];
	wifiFrame disco_frame = createWifiFrame(DISCOVERY_FRAME, 0, 0, 0, 0);
	char * disco_data = wifiFrameToChar(disco_frame);
	
	if(udp_driver_discover_network(31000,52400,(unsigned char *)disco_data, CONVERTED_WIFI_FRAME_SIZE ,(unsigned char *)disco_data, CONVERTED_WIFI_FRAME_SIZE , 5000, IP)<0) {
		printf("[Test] disco returns error <0\n");
		return;
	}
	
	printf("[Test] disco ip=%s\n",IP);
		
	if(udp_async_driver_init(31000,52400,IP)<0) {
		printf("[Test] init returns error <0\n");
		return;
	}	
	
	udp_async_driver_enable_read(&test_callback_fct,64);
	
	while(1) {
		getchar();
	}
}

void test_callback_fct(unsigned char * data, int size)
{
	if(size==CONVERTED_WIFI_FRAME_SIZE) {
		wifiFrame frame = wifiFrameFromChar((char *)data);		
		printf("[Test] L%d %s : seqNum%d type=%c data0=%d data1=%d data2=%d data3=%d\n",__LINE__,__FUNCTION__,frame.seqNum,frame.type,frame.data[0],frame.data[1],frame.data[2],frame.data[3]);		
	}
	else {
		printf("[Test] L%d %s : (%d bytes) Unknow frame %s\n",__LINE__,__FUNCTION__,size,data);		
	}
}
