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

void ardrone_program() 
{	
	//init
	if(initUSBCommunicationSync()!=0) { //usb
		return;
	}
	
	if(initCommunication()!=0) { //udp
		return;
	}

	int size ;
	Tdoa *arrayTdoa1 = NULL, *arrayTdoa2 = NULL, *arrayTdoa3 = NULL ;
	Likelyhood *arrayLikelyhood = NULL ;
	
	readFiles(&arrayTdoa1,&arrayTdoa2,&arrayTdoa3,&size) ;	

	char type;
	uint32_t tdoa1, tdoa2, tdoa3, tdoa4 ;
	uint32_t x, y, z ;
	
	while(1) 
	{	
		//read USB
		if(readUSBFrameSync(&type,&tdoa1,&tdoa2,&tdoa3,&tdoa4)==0) {

		arrayLikelyhood = createArrayLikelyhood(arrayTdoa1, arrayTdoa2, arrayTdoa3, size, tdoa1, tdoa2, tdoa3) ;

		sortArray(&arrayLikelyhood, size) ;

		//displayArray(arrayLikelyhood, size) ;

		x = arrayLikelyhood[0].position[0] ;
		y = arrayLikelyhood[0].position[1] ;
		z = arrayLikelyhood[0].position[2] ;
		
		sendFrame(type,x,y,z,0) ;
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




