#include "usb_protocol.h"


void readUSBFrame(unsigned char * data, int size){
	if(size==CONVERTED_SERIAL_FRAME_SIZE){
		serialFrame frame;
		retrieveReadFrame((uint8_t *)data, &frame);
				
		#ifdef DEBUG
			printf("[Debug] L%d %s : seqNum=%d type=%c data0=%d data1=%d data2=%d data3=%d crc=%d\n",__LINE__,__FUNCTION__,frame.seqNum,frame.type,frame.data[0],frame.data[1],frame.data[2],frame.data[3],frame.crc);		
		#endif
	}
}



uint8_t initUSBCommunication()
{
	if(usb_async_driver_init()==0){
		if(usb_async_driver_enable_read(&readUSBFrame, CONVERTED_SERIAL_FRAME_SIZE)==0){
			return 0;
		}
	}
	return 1;
}


uint8_t closeUSBCommunication(){
	if(usb_async_driver_close()==0)
		return 0;
	else
		return 1;
}
