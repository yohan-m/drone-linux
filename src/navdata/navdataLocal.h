#ifndef __NAVDATA_LOCAL__
#define __NAVDATA_LOCAL__

#include "navdataToPC.h"
#include "navdata_manager.h"
#include "struct.h"

#define IP_DRONE "127.0.0.1"
#define PORT_NAV_LOCAL 15000
#define NAV_HEADER 0x55667788

int fd_navDrone;

int initNavdataComm();

/**
 * \brief Function used to send a frame over wifi
 * \param[in]	data	data received and given by handler
 * \param[in]	size	size of the received data in bytes
 */
void readNav(unsigned char * data, int size);

int sendNav(unsigned char * data, int size);

/**
 * \brief        Closes the socket.
 * \return 		 0 for a successfull call, -1 otherwise
 */
int closeNavDataComm();

#endif
