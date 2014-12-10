/**
 * \file usb_protocol.h
 *
 * \brief Protocol level functions for USB communication
 *
 * \author Thomas Hoet
 *
 * \date 7 Nov 2014
 */

#ifndef __USB_PROTOCOL_SYNC__
#define __USB_PROTOCOL_SYNC__

#include "usb_driver.h"
#include "../../../common-sources/src/serialFrame.h"

/**
 * \brief        Multiplier for raw datas received over usb : datas are in semi ms -> convert into ms
 */
#define MULTIPLIER_RAW_TIMES 2

int checkSeqNum;
int cnt_missed;
int cnt_ok;

uint8_t readUSBFrameSync(char * type, int32_t * data0, int32_t * data1, int32_t * data2, int32_t * data3, int32_t * rss0, int32_t * rss1, int32_t * rss2, int32_t * rss3);

/**
 * \brief        Initialization of the socket and the callback function for reception.
 * \details      It must be called first
 * \return 		 0 for a successfull call, 1 if init failed
 */
uint8_t initUSBCommunicationSync();

/**
 * \brief        Closes the communication.
 * \return 		 0 for a successfull call, 1 otherwise
 */
uint8_t closeUSBCommunicationSync();


#endif
