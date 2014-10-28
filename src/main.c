#include "tests/leds_motors_test.h"
#include "tests/udp_test.h"
#include "tests/udp_async_test.h"
#include "tests/udp_disco_test.h"
#include "tests/udp_manager_test.h"

int main(int argc, char *argv[]) 
{
	printf("\nStart\n\n");

	test_udp_manager();

	printf("\nEnd\n\n");
	return 0;	
}

