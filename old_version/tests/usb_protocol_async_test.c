#include "usb_protocol_async_test.h"

void usbProtocolAsyncTest(){

	if(initUSBCommunication()!=0) {
		return;
	}
	
	while(1) {
		usleep(100);
	}
	
	closeUSBCommunication();
}

