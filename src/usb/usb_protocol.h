/**
 * \file usb_protocol.h
 *
 * \brief Protocol level functions for USB communication
 *
 * \author Thomas Hoet
 *
 * \date 5 Nov 2014
 */

#ifndef __USB_PROTOCOL__
#define __USB_PROTOCOL__

#include "usb_async_driver.h"
#include "../../../common-sources/src/serialFrame.h"

/**
 * \brief Function used to send a frame over usb
 * \param[in]	data	data received and given by handler
 * \param[in]	size	size of the received data in bytes
 */
void readUSBFrame(unsigned char * data, int size);

/**
 * \brief        Initialization of the socket and the callback function for reception
 * \details      It must be called first
 * \return 		 0 for a successfull call, 1 if init failed
 */
uint8_t initUSBCommunication();

/**
 * \brief        Closes the communication.
 * \return 		 0 for a successfull call, 1 otherwise
 */
uint8_t closeUSBCommunication();


#endif
