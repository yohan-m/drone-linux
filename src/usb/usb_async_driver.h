/**
 * \file usb_async_driver.h
 *
 * \brief Driver to reveice data from the usb (Asynchronous).
 *
 * \author Thomas Hoet
 *
 * \date 31 Oct 2014
 */

#ifndef USB_ASYNC_DRIVER_H
#define USB_ASYNC_DRIVER_H

#define _GNU_SOURCE

#include <stdio.h> 
#include <stdlib.h>
#include <string.h> 
#include <unistd.h>  
#include <fcntl.h>  
#include <errno.h>  
#include <termios.h>
#include <signal.h>

/**
 * \brief Path to the device.
 */
#define USB_ASYNC_DEV "/dev/ttyACM0"

/**
 * \brief Typedef of the callback function used to receive asynchronous data.	
 */
typedef void (*usb_function)(unsigned char * data, int size);

/**
 * \brief Reference the usb dev.
 */
int usb_async_device;

/**
 * \brief Packet size (receive).
 */
int usb_packet_size;

/**
 * \brief Function called when the driver receive data via USB.
 */
usb_function callback_receive_usb;

/**
 * \brief Initialize the driver.
 * \details It must be called one time before any other functions of this file.
 */
int usb_async_driver_init();

/**
 * \brief        Close the device.
 * \return 		 0 for a successfull call. A negative value on error.
 */
int usb_async_driver_close();

/**
 * \brief        Start to read via USB.
 * \param[in]    callback_receive_fct 	Function called when the driver read data.
 * \param[in]	 max_packet_size		Max packet size to read.
 * \return 		 0 for a successfull call. A negative value on error.
 */
int usb_async_driver_enable_read(usb_function callback_receive_fct, int max_packet_size);

/**
 * \brief        Handler called when the driver receive data.
 * \details 	 This handler analyses the data and calls the callback receive function if data are valids.
 * \param[in]	 sig Signal reference.
 */
void usb_async_driver_handler(int sig);




#endif
