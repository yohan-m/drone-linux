/**
 * \file udp_async_driver.h
 *
 * \brief Driver to exchange data over UDP (Asynchronous).
 *
 * \author Thomas Hoet
 *
 * \date 26 Oct 2014
 */

#ifndef UDP_async_driver_H
#define UDP_async_driver_H

#define _GNU_SOURCE
 
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h> 
#include <sys/types.h>
#include <sys/socket.h>
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#define MAX_SOCK_OPENED 5

/**
 * \brief Typedef of the callback function used to receive asynchronous data.	
 */
typedef void (*udp_function)(unsigned char * data, int size);

/**
 * \brief Store the port/adress informations.
 */
struct sockaddr_in async_local_sockaddr;

/**
 * \brief Store the port/adress informations.
 */
struct sockaddr_in async_remote_sockaddr;

static struct sockaddr_in tab_async_remote_sockaddr[MAX_SOCK_OPENED];

typedef struct{
	int fd;
	int ind_remote_sock;
} corresp_fd_remote_sock;

static corresp_fd_remote_sock tab_corresp_fd_remote_sock[MAX_SOCK_OPENED];

/**
 * \brief Max packet size (receive).
 */
int async_packet_size;

static int tab_fd[MAX_SOCK_OPENED];

static int ind_tab_fd = 0;

/**
 * \brief Table of function called when the driver receive data via UDP.
 */
static udp_function tab_callback[MAX_SOCK_OPENED];

static int ind_tab_callback = 0;


/**
 * \brief        Initialization of the socket.
 * \details      It must be called before the read/write/close/enable/disable functions.
 * \param[in]    local_port 	Local port used to receive data.
 * \param[in]	 remote_port 	remote port used to send data.
 * \param[in]	 remote_addr 	remote IP address to send/receive data.
 * \return 		 0 for a successfull call. A negative value on error.
 */
int udp_async_driver_init(int local_port, int remote_port, char * remote_addr, int * async_socket_fd);

/**
 * \brief        Close the socket.
 * \return 		 0 for a successfull call. A negative value on error.
 */
int udp_async_driver_close(int async_socket_fd);

/**
 * \brief        Start to read via UDP.
 * \param[in]    callback_receive_fct 	Function called when the driver read data.
 * \param[in]	 max_packet_size		Max packet size to read.
 * \return 		 0 for a successfull call. A negative value on error.
 */
int udp_async_driver_enable_read(udp_function callback_receive_fct, int max_packet_size, int async_socket_fd);

/**
 * \brief        Send data over UDP.
 * \param[in]    data 	Buffer to send.
 * \param[in]	 size	Size of the buffer.
 * \return 		 0 for a successfull call. A negative value on error.
 */
int udp_async_driver_write(unsigned char * data, int size, int async_socket_fd);

/**
 * \brief        Handler called when the driver receive data.
 * \details 	 This handler analyses the data and calls the callback receive function if data are valids.
 * \param[in]	 sig Signal reference.
 */
void udp_async_driver_handler(int sig);

#endif
