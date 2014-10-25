#include "udp_test.h"


void udp_read_test()
{
	udp_driver_init(31000,52400,"192.168.1.2");
	
	unsigned char data[64];
	
	udp_driver_read(data,64);
	udp_driver_read(data,64);
	udp_driver_read(data,64);
	udp_driver_read(data,64);
	udp_driver_read(data,64);
	
	udp_driver_close();
}


void udp_write_test()
{
	udp_driver_init(31000,52400,"192.168.1.2");
	
	unsigned char data[5];
	data[0]='t';
	data[1]='e';
	data[2]='s';
	data[3]='t';
	data[4]='\0';
	
	udp_driver_write(data,5);
	udp_driver_write(data,5);
	udp_driver_write(data,5);
	udp_driver_write(data,5);
	udp_driver_write(data,5);
	
	udp_driver_close();
}
