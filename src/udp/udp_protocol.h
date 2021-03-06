/**
 * \file udp_protocol.h
 *
 * \brief Protocol level functions for wireless communication
 *
 * \author Yohan Marchiset
 *
 * \date 29 Oct 2014
 */

#ifndef __UDP_PROTOCOL__
#define __UDP_PROTOCOL__

#include <pthread.h>
#include "../control/controlTask.h"
#include "udp_async_driver.h"
#include "udp_driver_discover.h"
#include "../../../common-sources/src/wifiFrame.h"

/**
 * \brief Maximum size to read from UDP communication
 */
#define MAX_PACKET_SIZE 64
/**
 * \brief Local (drone) port from where emission and reception will be done
 */
#define LOCAL_PORT 30000
/**
 * \brief Remote (PC) port to which data will be sent
 */
#define REMOTE_PORT 31000

/**
 * \brief IP of the remote PC
 */
char IP[IP_SIZE];

/**
 * \brief File descriptor of the UDP socket used for this communication
 */
int fd_protocol;

/**
 * \brief Mutex to secure the use of data within this communication thread
 */
static pthread_mutex_t mutex_udp_protocol = PTHREAD_MUTEX_INITIALIZER;

/**
 * \brief Function used to send a frame over wifi
 * \param[in]	type	type of the frame to create and send, either TIME_FRAME or DISTANCE_FRAME
 * \param[in]	data1	first data to send in the frame
 * \param[in]	data2	second data to send in the frame
 * \param[in]	data3	third data to send in the frame
   \param[in]	stateMission	state of the mission to send in the frame
 * \return 		0 on success, 1 if frame creation or communication failed
 */
uint8_t sendFrame(char type, uint32_t data1, uint32_t data2, uint32_t data3, char stateMission) ;

/**
 * \brief Function used to send a frame over wifi
 * \param[in]	data	data received and given by handler
 * \param[in]	size	size of the received data in bytes
 */
void readFrame(unsigned char * data, int size);

/**
 * \brief        Initialization of the socket and the callback function for reception
 * \details      It must be called first
 * \return 		 0 for a successfull call, 1 if init failed
 */
uint8_t initCommunication();

/**
 * \brief        Closes the socket.
 * \return 		 0 for a successfull call, 1 otherwise
 */
uint8_t closeCommunication();

#endif
