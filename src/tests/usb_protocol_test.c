#include "usb_protocol_test.h"

void usbProtocolTest()
{

	if(initUSBCommunicationSync()!=0) {
		return;
	}
	
	char type;
	uint32_t data0;
	uint32_t data1;
	uint32_t data2;
	uint32_t data3;
	
	while(1) {
		if(readUSBFrameSync(&type,&data0,&data1,&data2,&data3)==0) {
			//printf("[Test] L%d %s : type=%c data0=%d data1=%d data2=%d data3=%d\n",__LINE__,__FUNCTION__,type,data0,data1,data2,data3);	
		}
		else {
			//printf("[Test] L%d %s : read returns =! 0\n",__LINE__,__FUNCTION__);			
		}
	}
	
	closeUSBCommunicationSync();
}

