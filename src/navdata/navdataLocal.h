/**
 * \file navdataLocal.h
 *
 * \brief Asynchronous UDP communication to receive navdata on the drone
 *
 * \author Yohan Marchiset
 *
 * \date 05 Dec 2014
 */

#ifndef __NAVDATA_LOCAL__
#define __NAVDATA_LOCAL__

#include "navdataToPC.h"
#include "navdata_manager.h"
#include "struct.h"

/**
 * \brief IP loopback address (drone address)
 */
#define IP_DRONE "127.0.0.1"

/**
 * \brief Navdata port chosen on the drone to receive the navdata (thanks to port translation)
 */
#define PORT_NAV_LOCAL 15000

/**
 * \brief Navdata header value as defined in Parrot documentation
 */
#define NAV_HEADER 0x55667788

/**
 * \brief File descriptor of the UDP socket used for this communication
 */
int fd_navDrone;

/**
 * \brief Initialization of the UDP socket
 * \return 		0 on success, -1 otherwise
 */
int initNavdataComm();

/**
 * \brief Reception of navdata coming from the drone
 * \param[in]	data	data received and given by handler
 * \param[in]	size	size of the received data in bytes
 */
void readNav(unsigned char * data, int size);

/**
 * \brief Transmits the wanted packet to the navdataToPC communication
 * \param[in]	data	data to transmit
 * \param[in]	size	size of the data in bytes
 */
int sendNav(unsigned char * data, int size);

/**
 * \brief        Closes the socket.
 * \return 		 0 for a successfull call, -1 otherwise
 */
int closeNavDataComm();

#endif
