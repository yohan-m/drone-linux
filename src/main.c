#include "tests/udp_async_test.h"
#include "tests/udp_disco_test.h"
#include "tests/udp_manager_test.h"
#include "tests/udp_protocol_test.h"
#include "tests/usb_test.h"
#include "tests/usb_protocol_test.h"
#include "demo/com_demo.h"
#include "usb/usb_protocol_sync.h"
#include "udp/udp_protocol.h"

#include "localization/bddTdoa.h"
#include "localization/likelyhood.h"

#include <time.h>

void ardrone_program() 
{	
	//init
	if(initUSBCommunicationSync()!=0) { //usb
		return;
	}
	
	if(initCommunication()!=0) { //udp
		return;
	}

	char type;
	uint32_t tdoa1, tdoa2, tdoa3, tdoa4 ;
	float x, y, z, timeDebut, diff ;

	Tdoa *arrayTdoa1 = NULL, *arrayTdoa2 = NULL, *arrayTdoa3 = NULL ;
	int size = 0 ;

	readFiles(&arrayTdoa1,&arrayTdoa2,&arrayTdoa3,&size) ;	
	
	while(1) 
	{	
		//read USB
		if(readUSBFrameSync(&type,&tdoa1,&tdoa2,&tdoa3,&tdoa4)==0) {
		
		printf("tdoa1 : %f\n", (float)tdoa1*1/128) ;
		printf("tdoa2 : %f\n", (float)tdoa2*1/128) ;
		printf("tdoa3 : %f\n", (float)tdoa3*1/128) ;
		printf("tdoa4 : %f\n", (float)tdoa4*1/128) ;

		timeDebut = clock() ;
		computePosition(&x, &y, &z, tdoa1, tdoa2, tdoa3, tdoa4, arrayTdoa1, arrayTdoa2, arrayTdoa3,size) ;

		diff = (float)((float)clock()-(float)timeDebut) ;///((float)CLOCKS_PER_SEC) ;
		printf("temps calcul : %f\n",diff) ;

		printf("x : %f\n", x) ;
		printf("y : %f\n", y) ;
		printf("z : %f\n", z) ;

		sendFrame(type,(int)x*100,(int)y*100,(int)z*100) ;
		}
	}
	
	//close
	closeUSBCommunicationSync(); //usb
	closeCommunication(); //udp
}

int main(int argc, char *argv[]) 
{
	printf("\nStart\n\n");

	ardrone_program() ;
	//comDemo();

	printf("\nEnd\n\n");
	return 0;	
}




