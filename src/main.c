#include "tests/udp_async_test.h"
#include "tests/udp_disco_test.h"
#include "tests/udp_manager_test.h"
#include "tests/udp_protocol_test.h"
#include "tests/usb_test.h"
#include "tests/usb_protocol_test.h"
#include "demo/com_demo.h"
#include "usb/usb_protocol_sync.h"
#include "udp/udp_protocol.h"

void ardrone_program() 
{
	//init
	if(initUSBCommunicationSync()!=0) { //usb
		return;
	}
	
	if(initCommunication()!=0) { //udp
		return;
	}
	
	//main part of the program
	//blablabla...
	
	//close
	closeUSBCommunicationSync(); //usb
	closeCommunication(); //udp
}

int main(int argc, char *argv[]) 
{
	printf("\nStart\n\n");

	comDemo();

	printf("\nEnd\n\n");
	return 0;	
}




