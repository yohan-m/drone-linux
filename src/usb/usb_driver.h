/**
 * \file usb_driver.h
 *
 * \brief Driver to reveice data from the usb.
 *
 * \author Thomas Hoet
 *
 * \date 29 Oct 2014
 */

#ifndef USB_DRIVER_H
#define USB_DRIVER_H

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
#define USB_DEV "/dev/ttyUSB0"

/**
 * \brief Reference the usb dev.
 */
int usb_device;

/**
 * \brief Initialize the driver.
 * \details It must be called one time before any other functions of this file.
 */
int usb_driver_init();

/**
 * \brief        Close the device.
 * \return 		 0 for a successfull call. A negative value on error.
 */
int usb_driver_close();

/**
 * \brief        Receive data via USB.
 * \details 	 blocking function.
 * \param[out]   data 	Buffer to send.
 * \param[in]	 size	Size of the buffer.
 * \return 		 0 for a successfull call. A negative value on error.
 */
int usb_driver_read(unsigned char * data, int size);


#endif
