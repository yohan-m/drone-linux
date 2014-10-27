/**
 * \file udp_driver.h
 *
 * \brief Driver to exchange data over UDP.
 *
 * \author Thomas Hoet
 *
 * \date 19 Oct 2014
 */
 
#ifndef UDP_DRIVER_H
#define UDP_DRIVER_H

#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h> 
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <errno.h>

/**
 * \brief Store the port/adress information.
 */
struct sockaddr_in local_sockaddr;

/**
 * \brief Store the port/adress information.
 */
struct sockaddr_in remote_sockaddr;

/**
 * \brief Reference the socket.
 */
int socket_fd;

/**
 * \brief        Initialization of the socket.
 * \details      It must be called before the read/write/close functions.
 * \param[in]    local_port 	Local port used to receive data.
 * \param[in]	 remote_port 	remote port used to send data.
 * \param[in]	 remote_addr 	remote IP address to send/receive data.
 * \return 		 0 for a successfull call. A negative value on error.
 */
int udp_driver_init(int local_port, int remote_port, char * remote_addr);

/**
 * \brief        Close the socket.
 * \return 		 0 for a successfull call. A negative value on error.
 */
int udp_driver_close();

/**
 * \brief        Send data over UDP.
 * \param[in]    data 	Buffer to send.
 * \param[in]	 size	Size of the buffer.
 * \return 		 0 for a successfull call. A negative value on error.
 */
int udp_driver_write(unsigned char * data, int size);

/**
 * \brief        Receive data via UDP.
 * \details 	 blocking function.
 * \param[out]   data 	Buffer to send.
 * \param[in]	 size	Size of the buffer.
 * \return 		 0 for a successfull call. A negative value on error.
 */
int udp_driver_read(unsigned char * data, int size);

#endif
