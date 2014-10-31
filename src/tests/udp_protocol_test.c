#include "udp_protocol_test.h"

void udpProtocolTest(){
	initCommunication("127.0.0.1");
	sendFrame('t',25687,56682,4687,96475);
	closeCommunication();
}

