#include "leds_motors_manager.h"


int leds_motors_init()
{
    int err = leds_motors_driver_init();
	return err;
}

int leds_motors_close()
{
	return leds_motors_driver_close();
}


int set_leds(enum color led1, enum color led2, enum color led3, enum color led4)
{
    unsigned char cmd_l[2];

	//build the frame
    cmd_l[0] = 0x00;
    cmd_l[1] = 0x00;

    cmd_l[0] |= (1<<6) | (1<<5) | (1<<0); 
    cmd_l[1] |= (1<<7) | (1<<6) | (1<<5) | (1<<0); 

    if(led1==GREEN) {
        cmd_l[1] |= (1<<1);
    }
    else if(led1==ORANGE) {
        cmd_l[0] |= (1<<1);
        cmd_l[1] |= (1<<1);
    }
    else if(led1==RED) {
        cmd_l[0] |= (1<<1);
    }

    if(led2==GREEN) {
        cmd_l[1] |= (1<<2);
    }
    else if(led2==ORANGE) {
        cmd_l[0] |= (1<<2);
        cmd_l[1] |= (1<<2);
    }
    else if(led2==RED) {
        cmd_l[0] |= (1<<2);
    }

    if(led3==GREEN) {
        cmd_l[1] |= (1<<3);
    }
    else if(led3==ORANGE) {
        cmd_l[0] |= (1<<3);
        cmd_l[1] |= (1<<3);
    }
    else if(led3==RED) {
        cmd_l[0] |= (1<<3);
    }

    if(led4==GREEN) {
        cmd_l[1] |= (1<<4);
    }
    else if(led4==ORANGE) {
        cmd_l[0] |= (1<<4);
        cmd_l[1] |= (1<<4);
    }
    else if(led4==RED) {
        cmd_l[0] |= (1<<4);
    }

    int err = leds_motors_driver_write(cmd_l,2);    
    
    return err;
}


int set_leds_green()
{
    return set_leds(GREEN, GREEN, GREEN, GREEN);
}


int set_leds_orange()
{
    return set_leds(ORANGE, ORANGE, ORANGE, ORANGE);
}


int set_leds_red()
{
    return set_leds(RED, RED, RED, RED);
}


int set_leds_off()
{
    return set_leds(OFF, OFF, OFF, OFF);
}


int set_motors(int pwm1, int pwm2, int pwm3, int pwm4)
{
	unsigned char cmd_m[5];

	//check arguments
	if(pwm1<0) {
		pwm1=0;
	}
	else if(pwm1>511) {
		pwm1=511;
	}

	if(pwm2<0) {
		pwm2=0;
	}
	else if(pwm2>511) {
		pwm2=511;
	}

	if(pwm3<0) {
		pwm3=0;
	}
	else if(pwm3>511) {
		pwm3=511;
	}	
	
	if(pwm4<0) {
		pwm4=0;
	}
	else if(pwm4>511) {
		pwm4=511;
	}

	//build the frame
	cmd_m[0] = (0x20 | (pwm1 & 0x1ff)>>4);
	cmd_m[1] = ((pwm1 & 0x1ff)<<4) | ((pwm2 & 0x1ff)>>5);
	cmd_m[2] = ((pwm2 & 0x1ff)<<3) | ((pwm3 & 0x1ff)>>6);
	cmd_m[3] = ((pwm3 & 0x1ff)<<2) | ((pwm4 & 0x1ff)>>7);
	cmd_m[4] = ((pwm4 & 0x1ff)<<1) | (0 << 0);

	int err = leds_motors_driver_write(cmd_m,5);    

	return err;
}


int set_all_motors(int pwm)
{
	return set_motors(pwm,pwm,pwm,pwm);
}







