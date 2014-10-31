/**
 * \file udp_driver_discover.h
 *
 * \brief Functions to find the computer on the network.
 *
 * \author Thomas Hoet
 *
 * \date 19 Oct 2014
 */
 
#ifndef UDP_DRIVER_DISCOVER_H
#define UDP_DRIVER_DISCOVER_H

#define _GNU_SOURCE

#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <sys/types.h>
#include <sys/socket.h>
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#define IP_SIZE 16*sizeof(char)
#define MAX_DISCOVERY_WAIT_TIME 500
/**
 * \brief Store the port/adress informations.
 */
struct sockaddr_in disco_local_sockaddr;

/**
 * \brief Store the port/adress informations.
 */
struct sockaddr_in disco_remote_sockaddr;

/**
 * \brief Reference the socket.
 */
int disco_socket_fd;

/**
 * \brief Response frame.
 */
unsigned char * disco_response_frame;

/**
 * \brief Responde size.
 */
int disco_response_size;

/**
 * \brief Store the IP of the response.
 */
char * disco_ip;

/**
 * \brief Check if we found the IP.
 */
int disco_found;

/**
 * \brief        Find the address of the computer on the network.
 * \param[in]	 local_port			local port used to receive data.
 * \param[in]    remote_port 		remote port used to send data.
 * \param[in]	 discovery_frame	Broadcasted frame.
 * \param[in]	 discovery_size 	Size of the broadcasted frame.
 * \param[in]	 response_frame		Computer's response frame.
 * \param[in]	 response_size	 	Size of the response frame.
 * \param[in]	 delay_ms			duration of the read (when waiting for a response from the computer).
 * \param[out]	 IP 				IP of the computer if found (empty if not found).
 * \return 		 0 for a successfull call. A negative value on error.
 */
int udp_driver_discover_network(int local_port, int remote_port, unsigned char * discovery_frame, int discovery_size, unsigned char * response_frame, int response_size, int delay_ms, char * IP);

/**
 * \brief        Handler called when the driver receive data.
 * \details 	 This handler analyses the data and calls the callback receive function if data are valids.
 * \param[in]	 sig Signal reference.
 * \return 		 0 for a successfull call. A negative value on error.
 */
void udp_driver_discover_handler(int sig);

#endif
