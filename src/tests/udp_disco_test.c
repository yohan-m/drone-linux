#include "udp_disco_test.h"

void test_udp_disco()
{
	char * IP = malloc(IP_SIZE);
	if(udp_driver_discover_network(31000,52400,(unsigned char *)"discoframe", 10,(unsigned char *)"respofr", 7, 5000, IP)<0) {
		printf("[Test] disco returns error <0\n");
		return;
	}
	else {
		printf("[Test] disco ip=%s\n",IP);
		
		if(udp_driver_init(31000,52400,IP)<0) {
			printf("[Test] init returns error <0\n");
			return;
		}
		
		//try to receive data with this IP to check if the format is valid
		unsigned char data[64];
		udp_driver_read(data,64);
	}	
}
