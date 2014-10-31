#include "udp_protocol.h"
#include "../../../common-sources/src/wifiFrame.h"


uint8_t sendFrame(char type, uint32_t data1, uint32_t data2, uint32_t data3, uint32_t data4){
	wifiFrame f = createWifiFrame(type, data1, data2, data3, data4);
	char * convertedFrame = wifiFrameToChar(f);
	if(udp_async_driver_write((unsigned char *)convertedFrame, CONVERTED_WIFI_FRAME_SIZE)==0)
		return 0;
	else
		return 1;
}


void readFrame(unsigned char * data, int size){
	if(size==CONVERTED_WIFI_FRAME_SIZE){
		wifiFrame f = wifiFrameFromChar((char*)data);
		//printf("frame:\nseqnum=%d\ntype=%c\ndata=%d; %d; %d; %d\n",f.seqNum,f.type,f.data[0],f.data[1],f.data[2],f.data[3]);
	}
}


uint8_t initCommunication(char * remote_addr){
	if(udp_async_driver_init(LOCAL_PORT, REMOTE_PORT,remote_addr)==0){
		if(udp_async_driver_enable_read(&readFrame, MAX_PACKET_SIZE)==0){
			return 0;
		}
	}
	return 1;
}


uint8_t closeCommunication(){
	if(udp_async_driver_close()==0)
		return 0;
	else
		return 1;
}
