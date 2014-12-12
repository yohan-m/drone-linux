#include "usb_protocol_sync.h"


uint8_t readUSBFrameSync(char * type, float * data0, float * data1, float * data2, float * data3, int32_t * rss0, int32_t * rss1, int32_t * rss2, int32_t * rss3)
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
		
		if(cnt_ok%10==0) {
			#ifdef DEBUG_INFO
				printf("[Debug] L%d %s : %d Ok , %d missed\n",__LINE__,__FUNCTION__,cnt_ok,cnt_missed);
			#endif			
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
	*data0 = -(float)frame.data[0]/DIVIDER_RAW_TIMES;
	*data1 = -(float)frame.data[1]/DIVIDER_RAW_TIMES;
	*data2 = -(float)frame.data[2]/DIVIDER_RAW_TIMES;
	*data3 = -(float)frame.data[3]/DIVIDER_RAW_TIMES; 

	
	*rss0 = frame.rss[0];
	*rss1 = frame.rss[1];
	*rss2 = frame.rss[2];
	*rss3 = frame.rss[3];
		
	return 0;
}


uint8_t initUSBCommunicationSync()
{
	#ifdef DEBUG_INFO
		printf("[Debug] L%d %s : Initializing USB ...\n",__LINE__,__FUNCTION__);		
	#endif
	if(usb_driver_init()==0)
	{
		checkSeqNum = -1;
		cnt_ok = 0;
		cnt_missed = 0;
		#ifdef DEBUG_INFO
			printf("[Debug] L%d %s : Done !\n",__LINE__,__FUNCTION__);		
		#endif
		return 0;
	}
	return 1;
}


uint8_t closeUSBCommunicationSync()
{
	#ifdef DEBUG_INFO
		printf("[Debug] L%d %s : Closing USB ...\n",__LINE__,__FUNCTION__);		
	#endif
	if(usb_driver_close()==0) {
		#ifdef DEBUG_INFO
			printf("[Debug] L%d %s : Done !\n",__LINE__,__FUNCTION__);		
		#endif
		return 0;
	}
	return 1;
}
