#include "navdataLocal.h"

int initNavdataComm(){
	#ifdef DEBUG_INFO
		printf("[Debug] L%d %s : Initializing navdata drone ...\n",__LINE__,__FUNCTION__);			
	#endif

	if(udp_async_driver_init(PORT_NAV_LOCAL, NAVDATA_PORT, IP_DRONE, &fd_navDrone)==0){
		if(udp_async_driver_enable_read(&readNav, NAVDATA_MAX_PACKET_SIZE, fd_navDrone)==0){
			#ifdef DEBUG_INFO
				printf("[Debug] L%d %s : Done !\n",__LINE__,__FUNCTION__);		
			#endif
			unsigned char init[] = {1,0,0,0,0,0,0,0,0,0,0,0,0,0};
			if(udp_async_driver_write(init, 14, fd_navDrone)>=0) {
					#ifdef DEBUG_INFO
						printf("[Debug] L%d %s : init of navdata done\n",__LINE__,__FUNCTION__);		
					#endif
				return 0;
				}
			}

			return -1;
	}
	return -1;
}

void readNav(unsigned char * data, int size){
	#ifdef DEBUG_INFO
		printf("[Debug] L%d %s : Received navdata frame\n",__LINE__,__FUNCTION__);			
	#endif
	if(size>24){
		Navdata *nav = (Navdata*)data;
		NavdataDemo *nd = (NavdataDemo*)&nav->options[0];
		sendNav(data,size);
	}
}


int sendNav(unsigned char * data, int size){
	if(sendNavToPC(data,size)>=0){
		return 0;
	}
	else{
		return -1;
	}
}


int closeNavDataComm(){
	#ifdef DEBUG_INFO
		printf("[Debug] L%d %s : Closing NavData ...\n",__LINE__,__FUNCTION__);		
	#endif
	if(udp_async_driver_close(fd_navDrone)==0) {
			#ifdef DEBUG_INFO
				printf("[Debug] L%d %s : Done !\n",__LINE__,__FUNCTION__);		
			#endif
		return 0;
	}
	else {
		return 1;
	}
}
