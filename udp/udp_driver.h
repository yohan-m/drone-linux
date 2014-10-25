/* 
 * File:   udp_driver.h
 * Author: Thomas Hoet
 * Description : Driver to exchange data over UDP.
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

//variables to handle the ports and the addresses.
struct sockaddr_in local_sockaddr, remote_sockaddr;

//variable used to reference the socket.
int socket_fd;

//init the driver, it must be called before any other function of this file.
int udp_driver_init(int local_port, int remote_port, char * remote_addr);

//close the driver.
int udp_driver_close();

//write data over udp.
int udp_driver_write(unsigned char * data, int size);

//read data via udp.
int udp_driver_read(unsigned char * data, int size);

#endif
