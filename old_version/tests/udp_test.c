#include "udp_test.h"


void test_udp_read()
{
	unsigned char data[64];
	
	udp_driver_init(31000,52400,"192.168.1.2");	
	
	udp_driver_read(data,64);
	udp_driver_read(data,64);
	udp_driver_read(data,64);
	udp_driver_read(data,64);
	udp_driver_read(data,64);
	
	udp_driver_close();
}


void test_udp_write()
{	
	udp_driver_init(31000,52400,"10.202.13.35");
	
	udp_driver_write((unsigned char *)"test",5);
	udp_driver_write((unsigned char *)"test",5);
	udp_driver_write((unsigned char *)"test",5);
	udp_driver_write((unsigned char *)"test",5);
	
	udp_driver_close();
}
