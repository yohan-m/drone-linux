/**
 * \file control.h
 *
 * \brief Send specific frame to control the drone.
 *
 * \author Thomas Hoet
 *
 * \date 3 Dec 2014
 */

#ifndef CONTROL_H
#define CONTROL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../udp/udp_async_driver.h"

#define CTRL_PORT 5556
#define CTRL_PORT_LOCAL 16000
#define IP_DRONE "127.0.0.1"
#define CTRL_MAX_PACKET_SIZE 512

/**
 * \brief File descriptor of the socket.
 */
int fd_ctrlDrone;

/**
 * \brief Initialization function. This function must be called at the beginning.
 */
int initControl();

/**
 * \brief Ask the drone to send the navdata.
 * \param[in] 	seqNum
 */
void sendNavDataInit(int seqNum);

/**
 * \brief Reset the communication watchdog.
 * \param[in] 	seqNum
 */
void sendResetWatchdog(int seqNum);

/**
 * \brief Leave the emergency mode on the drone.
 * \param[in] 	seqNum
 */
void sendEmergency(int seqNum);

/**
 * \brief Calibrate the horizontal plane.
 * \param[in] 	seqNum
 */
void sendCalibHPlan(int seqNum);

/**
 * \brief Calibrate the magnetometer.
 * \param[in] 	seqNum
 */
void sendCalibMagn(int seqNum);

/**
 * \brief Take off.
 * \param[in] 	seqNum
 */
void sendTakeOff(int seqNum);

/**
 * \brief Land.
 * \param[in] 	seqNum
 */
void sendLand(int seqNum);

/**
 * \brief Send a movement to the drone.
 * \param[in] 	seqNum
 * \param[in] 	flag
 * \param[in] 	frontBackTilt
 * \param[in] 	leftRightTilt
 * \param[in] 	verticalSpeed
 * \param[in] 	angularSpeed
 */
void sendMovement(int seqNum, int flag, float frontBackTilt, float leftRightTilt, float verticalSpeed, float angularSpeed);

/**
 *  PRIVATE
 */

/**
 * \brief Convert a number into a char*.
 * \param[in] 	number	Number to convert
 * \param[out]  str		String (number converted)
 * \param[out]  size	Size of the str
 */
void numberToString(int number, char * str, int * size);

/**
 * \brief Send the command to the drone.
 * \param[in]	data	Data to send
 * \param[in]	size	Size of the data
 */
void writeCmd(char * data, int size);

/**
 * \brief Read data on this socket (not used in this version).
 * \param[out]	data	Buffer
 * \param[in]	size	Size of the data
 */
void readCtrl(unsigned char * data, int size);

/**
 * \brief Close the socket.
 */
int closeCtrl();

#endif
