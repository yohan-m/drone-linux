#include "leds_motors_test.h"


void test_led1()
{
	leds_motors_init();

	set_leds(OFF,OFF,OFF,OFF);
	usleep(500000);
	set_leds(GREEN,OFF,OFF,OFF);
	usleep(500000);
	set_leds(ORANGE,OFF,OFF,OFF);
	usleep(500000);
	set_leds(RED,OFF,OFF,OFF);
	usleep(500000);
	set_leds(OFF,OFF,OFF,OFF);
	
	leds_motors_close();
}


void test_led2()
{
	leds_motors_init();

	set_leds(OFF,OFF,OFF,OFF);
	usleep(500000);
	set_leds(OFF,GREEN,OFF,OFF);
	usleep(500000);
	set_leds(OFF,ORANGE,OFF,OFF);
	usleep(500000);
	set_leds(OFF,RED,OFF,OFF);
	usleep(500000);
	set_leds(OFF,OFF,OFF,OFF);
	
	leds_motors_close();
}


void test_led3()
{
	leds_motors_init();

	set_leds(OFF,OFF,OFF,OFF);
	usleep(500000);
	set_leds(OFF,OFF,GREEN,OFF);
	usleep(500000);
	set_leds(OFF,OFF,ORANGE,OFF);
	usleep(500000);
	set_leds(OFF,OFF,RED,OFF);
	usleep(500000);
	set_leds(OFF,OFF,OFF,OFF);
	
	leds_motors_close();
}


void test_led4()
{
	leds_motors_init();

	set_leds(OFF,OFF,OFF,OFF);
	usleep(500000);
	set_leds(OFF,OFF,OFF,GREEN);
	usleep(500000);
	set_leds(OFF,OFF,OFF,ORANGE);
	usleep(500000);
	set_leds(OFF,OFF,OFF,RED);
	usleep(500000);
	set_leds(OFF,OFF,OFF,OFF);
	
	leds_motors_close();
}


void test_all_leds()
{
	leds_motors_init();

	set_leds_off();
	usleep(500000);
	set_leds_green();
	usleep(500000);
	set_leds_orange();
	usleep(500000);
	set_leds_red();
	usleep(500000);
	set_leds_off();
	
	leds_motors_close();
}


void test_motor1()
{
	leds_motors_init();
	
	int i;
	for( i=0 ; i<FREQUENCY_MOTOR_HZ*2 ; i++ ) {
		set_motors(150,0,0,0);
		usleep(PERIOD_MOTOR_US);
	}
	
	set_motors(0,0,0,0);
	
	leds_motors_close();
}


void test_motor2()
{
	leds_motors_init();
	
	int i;
	for( i=0 ; i<FREQUENCY_MOTOR_HZ*5 ; i++ ) {
		set_motors(0,50,0,0);
		usleep(PERIOD_MOTOR_US);
	}
	
	set_motors(0,0,0,0);
}


void test_motor3()
{
	leds_motors_init();
	
	int i;
	for( i=0 ; i<FREQUENCY_MOTOR_HZ*5 ; i++ ) {
		set_motors(0,0,50,0);
		usleep(PERIOD_MOTOR_US);
	}
	
	set_motors(0,0,0,0);
	
	leds_motors_close();
}


void test_motor4()
{
	leds_motors_init();
	
	int i;
	for( i=0 ; i<FREQUENCY_MOTOR_HZ*5 ; i++ ) {
		set_motors(0,0,0,50);
		usleep(PERIOD_MOTOR_US);
	}
	
	set_motors(0,0,0,0);
	
	leds_motors_close();
}

void test_all_motors()
{
	leds_motors_init();

		int i;
	for( i=0 ; i<FREQUENCY_MOTOR_HZ*5 ; i++ ) {
		set_all_motors(63);
		usleep(PERIOD_MOTOR_US);
	}
	
	set_all_motors(0);
	
	leds_motors_close();
}
