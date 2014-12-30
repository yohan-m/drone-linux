#include "navdataToPC.h"

int initNavdataCommPC(){
	#ifdef DEBUG_INFO
		printf("[Debug] L%d %s : Initializing navdata to pc ...\n",__LINE__,__FUNCTION__);			
	#endif

	if(udp_async_driver_init(NAVDATA_EMISSION_PORT, NAVDATA_PORT,IP, &fd_navPC)==0){
		if(udp_async_driver_enable_read(&readNavPC, NAVDATA_MAX_PACKET_SIZE, fd_navPC)==0){
			#ifdef DEBUG_INFO
				printf("[Debug] L%d %s : Done !\n",__LINE__,__FUNCTION__);		
			#endif
	
		return 0;
		}
	}

	return -1;
}


void readNavPC(unsigned char * data, int size){
	#ifdef DEBUG_INFO
		printf("[Debug] L%d %s : Received navdata frame\n",__LINE__,__FUNCTION__);			
	#endif
}


int sendNavToPC(unsigned char * data, int size){
	int sent = 0;
	if((sent=udp_async_driver_write(data, size,fd_navPC))>=0) {
		#ifdef DEBUG_INFO
			printf("[Debug] L%d %s : Write navdata to pc OK : transmitted %d bytes\n",__LINE__,__FUNCTION__,size);		
		#endif
		return 0;
	}
	else {
		return 1;
	}
}


int closeNavDataCommPC(){
	#ifdef DEBUG_INFO
		printf("[Debug] L%d %s : Closing NavData ...\n",__LINE__,__FUNCTION__);		
	#endif
	if(udp_async_driver_close(fd_navPC)==0) {
			#ifdef DEBUG_INFO
				printf("[Debug] L%d %s : Done !\n",__LINE__,__FUNCTION__);		
			#endif
		return 0;
	}
	else {
		return 1;
	}
}
