/**
 * \file leds_motors_driver.h
 *
 * \brief Driver to send data to the leds/motors uart.
 *
 * \author Thomas Hoet
 *
 * \date 12 Oct 2014
 */

#ifndef LEDS_MOTORS_DRIVER_H
#define LEDS_MOTORS_DRIVER_H

#include <stdio.h> 
#include <stdlib.h>
#include <string.h> 
#include <unistd.h>  
#include <fcntl.h>  
#include <errno.h>  
#include <termios.h>

/**
 * \brief Path to the device.
 */
#define LEDS_MOTORS_DEV "/dev/ttyO0"

#define GPIO_ERROR_READ  176
#define GPIO_ERROR_RESET 175
#define GPIO_M1 171
#define GPIO_M2 172
#define GPIO_M3 173
#define GPIO_M4 174

/**
 * \brief Reference the uart.
 */
int leds_motors_device;

/**
 * \brief Close the driver.
 */
int leds_motors_driver_close();

/**
 * \brief Initialize the driver.
 * \details It must be called one time before any other functions of this file.
 */
int leds_motors_driver_init();

/**
 * \brief        Send data to the leds/motors uart.
 * \param[in]    data 	Buffer to send.
 * \param[in]	 size	Size of the buffer.
 * \return 		 0 for a successfull call. A negative value on error.
 */
int leds_motors_driver_write(unsigned char * data, int size);

int gpio_set (int nr, int val);
int motor_cmd(int file, unsigned char cmd, unsigned char *reply, int replylen);

#endif
