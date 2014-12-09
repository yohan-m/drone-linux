#include "./com_demo.h"

void comDemo()
{
	//init USB
	if(initUSBCommunicationSync()!=0) {
		return;
	}
	
	//init UDP
	if(initCommunication()!=0) {
		return;
	}
	
	usleep(1000000);
	
	char type;
	uint32_t data0;
	uint32_t data1;
	uint32_t data2;
	uint32_t data3;	
	uint32_t rss0;
	uint32_t rss1;
	uint32_t rss2;
	uint32_t rss3;	
	
	while(1) {	
		//read USB
		if(readUSBFrameSync(&type,&data0,&data1,&data2,&data3,&rss0,&rss1,&rss2,&rss3)==0) {
			//send UDP
			sendFrame(type,data0,data1,data2,STOP_MISSION);
		}
	}
	
	closeUSBCommunicationSync();
}
