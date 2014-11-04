#include "tests/leds_motors_test.h"
#include "tests/udp_test.h"
#include "tests/udp_async_test.h"
#include "tests/udp_disco_test.h"
#include "tests/udp_manager_test.h"
#include "tests/usb_test.h"
#include "tests/usb_async_test.h"

int main(int argc, char *argv[]) 
{
	printf("\nStart\n\n");

	test_usb_async();

	printf("\nEnd\n\n");
	return 0;	
}

