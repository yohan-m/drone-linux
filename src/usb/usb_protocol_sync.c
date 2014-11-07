#include "usb_protocol_sync.h"


uint8_t readUSBFrameSync(char * type, uint32_t * data0, uint32_t * data1, uint32_t * data2, uint32_t * data3)
{
	unsigned char data[CONVERTED_SERIAL_FRAME_SIZE];
	
	int done = 0;
	unsigned char sync1='A';
	unsigned char sync2='A';
	
	int cnt_bytes = usb_driver_read(&sync2,1);
	if(cnt_bytes<0) {
		return 1;
	}
	
	while(done==0) {
		sync1=sync2;
		cnt_bytes = usb_driver_read(&sync2,1);
		if(cnt_bytes<0) {
			return 2;
		}
		
		if(sync1==SYNC_CHAR_1 && sync2==SYNC_CHAR_2) {
			cnt_bytes = usb_driver_read(data,CONVERTED_SERIAL_FRAME_SIZE);
			if(cnt_bytes<0) {
				return 3;
			}
			if(cnt_bytes==CONVERTED_SERIAL_FRAME_SIZE) {
				done=1;
			}
		}
	}

	serialFrame frame;
	if(retrieveReadFrame((uint8_t *)data, &frame)!=0) {
		printf("[Error] L%d %s : Incorrect CRC\n",__LINE__,__FUNCTION__);	
		return 4;	
	}
	
	if(checkSeqNum!=-1) {
		if(frame.seqNum==0 && checkSeqNum==MAX_SERIAL_SEQ_NUM) {
			cnt_ok++;
		}
		else if(frame.seqNum==(checkSeqNum+1)) {
			cnt_ok++;		
		}
		else {
			cnt_missed++;
		}
		
		if(cnt_ok%1000==0) {
			printf("[Warning] L%d %s : %d Ok , %d missed\n",__LINE__,__FUNCTION__,cnt_ok,cnt_missed);			
		}
		
		checkSeqNum=frame.seqNum;
	}
	else {
		checkSeqNum=frame.seqNum;	
	}
				
	#ifdef DEBUG_USB_PROTOCOL
			printf("[Debug] L%d %s : seqNum=%d type=%c data0=%08X data1=%08X data2=%08X data3=%08X\n",__LINE__,__FUNCTION__,frame.seqNum,frame.type,frame.data[0],frame.data[1],frame.data[2],frame.data[3]);		
	#endif
	
	*type = frame.type;
	*data0 = frame.data[0];
	*data1 = frame.data[1];
	*data2 = frame.data[2];
	*data3 = frame.data[3];
		
	return 0;
}



uint8_t initUSBCommunicationSync()
{
	if(usb_driver_init()==0){
		checkSeqNum = -1;
		cnt_ok = 0;
		cnt_missed = 0;
		#ifdef DEBUG_USB_PROTOCOL
			printf("[Debug] L%d %s : USB init ok\n",__LINE__,__FUNCTION__);		
		#endif
		return 0;
	}
	return 1;
}


uint8_t closeUSBCommunicationSync(){
	if(usb_driver_close()==0) {
		#ifdef DEBUG_USB_PROTOCOL
			printf("[Debug] L%d %s : close USB ok\n",__LINE__,__FUNCTION__);		
		#endif
		return 0;
	}
	return 1;
}
