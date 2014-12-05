#include "udp_protocol.h"

uint8_t sendFrame(char type, uint32_t data1, uint32_t data2, uint32_t data3, char stateMission){
	wifiFrame f = createWifiFrame(type, data1, data2, data3,0,CMD_NONE, stateMission);
	//char * convertedFrame = wifiFrameToChar(f);
	if(udp_async_driver_write((unsigned char *)&f, CONVERTED_WIFI_FRAME_SIZE, fd_protocol)>0) {
		#ifdef DEBUG_UDP_PROTOCOL
			printf("[Debug] L%d %s : Write OK !\n",__LINE__,__FUNCTION__);		
		#endif
		return 0;
	}
	else {
		return 1;
	}
}


void readFrame(unsigned char * data, int size){
	if(size==CONVERTED_WIFI_FRAME_SIZE)
	{
        wifiFrame wf = *(wifiFrame*)data;//wifiFrameFromChar((char*)data);
		float pitch=0.0;
		float roll=0.0;
		float angular_speed=0.0;
		float vertical_speed=0.0;
		int moveAsked = 0;
		switch(wf.type){
			case COMMAND_FRAME :
				
				if(wf.cmd & CMD_FWD == CMD_FWD){
					moveAsked = 1;
					pitch -= MOVE_AMPLITUDE;
				}
				if(wf.cmd & CMD_BWD == CMD_BWD){
					moveAsked = 1;
					pitch += MOVE_AMPLITUDE;
				}
				if(wf.cmd & CMD_LEFT == CMD_LEFT){
					moveAsked = 1;
					roll -= MOVE_AMPLITUDE;
				}
				if(wf.cmd & CMD_RIGHT == CMD_RIGHT){
					moveAsked = 1;
					roll += MOVE_AMPLITUDE;
				}
				if(wf.cmd & CMD_UP == CMD_UP){
					moveAsked = 1;
					vertical_speed += SPEED_AMPLITUDE;
				}
				if(wf.cmd & CMD_DOWN == CMD_DOWN){
					moveAsked = 1;
					vertical_speed -= SPEED_AMPLITUDE;
				}
				if(wf.cmd & CMD_ROTATE_RIGHT == CMD_ROTATE_RIGHT){
					moveAsked = 1;
					angular_speed += SPEED_AMPLITUDE;
				}
				if(wf.cmd & CMD_ROTATE_LEFT == CMD_ROTATE_LEFT){
					moveAsked = 1;
					angular_speed -= SPEED_AMPLITUDE;
				}
				if(wf.cmd & CMD_TAKE_OFF == CMD_TAKE_OFF){
					takeOff();
				}
				if(wf.cmd & CMD_LAND == CMD_LAND){
					land();
				}
				if(wf.cmd & CMD_FTRIM == CMD_FTRIM){
					calibHor();
				}
				if(wf.cmd & CMD_EMERGENCY == CMD_EMERGENCY){
					emergency();
				}
				if(wf.cmd & CMD_INIT_NAVDATA == CMD_INIT_NAVDATA){
					initNavData();
				}
				if(wf.cmd & CMD_CALIB_MAGNO == CMD_CALIB_MAGNO){
					calibMagn();
				}
				if(moveAsked){
					move(pitch, roll, angular_speed, vertical_speed);
				}
				break;
			
			case MISSION_FRAME:
				if (wf.stateMission == LAUNCH_MISSION){
					executeMission((float)wf.positions[0], (float)wf.positions[1], (float)wf.positions[2], (float)wf.angle);
				}
				else if (wf.stateMission == STOP_MISSION){
					executeManual();
				}
				break;
				
			case PC_CTRL:
				enableControl(0);
				break;
				
			case DRONE_CTRL:
				enableControl(1);
				break;
			
			default:
				break;
		}
		
		//printf("frame:\nseqnum=%d\ntype=%c\ndata=%d; %d; %d; %d\n",f.seqNum,f.type,f.positions[0],f.positions[1],f.positions[2],f.angle);
	}
}


uint8_t initCommunication(){
	#ifdef DEBUG_INFO
		printf("[Debug] L%d %s : Initializing UDP ...\n",__LINE__,__FUNCTION__);			
	#endif
	//char IP[IP_SIZE];
	wifiFrame disco_frame = createDiscoveryFrame();
	//char * disco_data = wifiFrameToChar(disco_frame);
	// waiting for PC to answer discovery frame (to get its IP for future communication)
	while(udp_driver_discover_network(LOCAL_PORT,REMOTE_PORT,(unsigned char *)&disco_frame, CONVERTED_WIFI_FRAME_SIZE ,(unsigned char *)&disco_frame, CONVERTED_WIFI_FRAME_SIZE , MAX_DISCOVERY_WAIT_TIME, IP)<0) {
		printf("[Warning] L%d %s : Can't find a computer\n",__LINE__,__FUNCTION__);			
	}

	#ifdef DEBUG_INFO
		printf("[Debug] L%d %s : Computer found %s\n",__LINE__,__FUNCTION__,IP);			
	#endif
	
	// initializing communication with PC
	if(udp_async_driver_init(LOCAL_PORT, REMOTE_PORT,IP, &fd_protocol)==0){
		if(udp_async_driver_enable_read(&readFrame, MAX_PACKET_SIZE, fd_protocol)==0){
			#ifdef DEBUG_INFO
				printf("[Debug] L%d %s : Done !\n",__LINE__,__FUNCTION__);		
			#endif
			return 0;
		}
	}
	return 1;
}


uint8_t closeCommunication(){
	#ifdef DEBUG_INFO
		printf("[Debug] L%d %s : Closing UDP ...\n",__LINE__,__FUNCTION__);		
	#endif
	if(udp_async_driver_close(fd_protocol)==0) {
			#ifdef DEBUG_INFO
				printf("[Debug] L%d %s : Done !\n",__LINE__,__FUNCTION__);		
			#endif
		return 0;
	}
	else {
		return 1;
	}
}
