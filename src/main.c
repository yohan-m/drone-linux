#include "tests/udp_async_test.h"
#include "tests/udp_disco_test.h"
#include "tests/udp_manager_test.h"
#include "tests/udp_protocol_test.h"
#include "tests/usb_test.h"
#include "tests/usb_protocol_test.h"
#include "demo/com_demo.h"

int main(int argc, char *argv[]) 
{
	printf("\nStart\n\n");

	comDemo();

	printf("\nEnd\n\n");
	return 0;	
}

