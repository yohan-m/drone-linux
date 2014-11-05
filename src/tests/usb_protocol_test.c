#include "usb_protocol_test.h"

void usbProtocolTest(){

	if(initUSBCommunication()!=0) {
		return;
	}
	
	while(1) {
		usleep(100);
	}
	
	closeUSBCommunication();
}

