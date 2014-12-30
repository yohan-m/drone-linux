/**
 * \file navdataToPC.h
 *
 * \brief Asynchronous UDP communication to transmit navdata to PC
 *
 * \author Yohan Marchiset
 *
 * \date 05 Dec 2014
 */

#ifndef __NAVDATA_TO_PC__
#define __NAVDATA_TO_PC__

#include "../udp/udp_protocol.h"

/**
 * \brief Navdata emission and reception port according to Parrot documentation
 */
#define NAVDATA_PORT 5554

/**
 * \brief Navdata port chosen on the drone to transmit the navdata to the PC
 */
#define NAVDATA_EMISSION_PORT 50000

/**
 * \brief Maximum size of the navdata packets
 */
#define NAVDATA_MAX_PACKET_SIZE 1024

/**
 * \brief File descriptor of the UDP socket used for this communication
 */
int fd_navPC;

/**
 * \brief Initialization of the UDP socket
 * \return 		0 on success, -1 otherwise
 */
int initNavdataCommPC();

/**
 * \brief Reception of navdata coming from the PC (should never be called)
 * \param[in]	data	data received and given by handler
 * \param[in]	size	size of the received data in bytes
 */
void readNavPC(unsigned char * data, int size);

/**
 * \brief Sends the wanted packet to the PC via the above mentioned file descriptor
 * \param[in]	data	data to send
 * \param[in]	size	size of the data in bytes
 */
int sendNavToPC(unsigned char * data, int size);

/**
 * \brief        Closes the socket.
 * \return 		 0 for a successfull call, -1 otherwise
 */
int closeNavDataCommPC();

#endif
