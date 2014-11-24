#include "udp_protocol_test.h"

void udpProtocolTest(){
	initCommunication("192.168.0.4");
	sendFrame('t',25687,56682,4687);
	closeCommunication();
}

