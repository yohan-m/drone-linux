#ifndef __NAVDATA_TO_PC__
#define __NAVDATA_TO_PC__

#include "../udp/udp_protocol.h"

#define NAVDATA_PORT 5554
#define NAVDATA_EMISSION_PORT 50000
#define NAVDATA_MAX_PACKET_SIZE 1024

int fd_navPC;

int initNavdataCommPC();

/**
 * \brief Function used to send a frame over wifi
 * \param[in]	data	data received and given by handler
 * \param[in]	size	size of the received data in bytes
 */
void readNavPC(unsigned char * data, int size);

int sendNavToPC(unsigned char * data, int size);

/**
 * \brief        Closes the socket.
 * \return 		 0 for a successfull call, -1 otherwise
 */
int closeNavDataCommPC();

#endif
