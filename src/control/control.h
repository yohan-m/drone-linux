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

int fd_ctrlDrone;

int initControl();

void sendNavDataInit(int seqNum);

void sendResetWatchdog(int seqNum);

void sendEmergency(int seqNum);

void sendCalibHPlan(int seqNum);

void sendCalibMagn(int seqNum);

void sendTakeOff(int seqNum);

void sendLand(int seqNum);

void sendMovement(int seqNum, int flag, float frontBackTilt, float leftRightTilt, float verticalSpeed, float angularSpeed);

void numberToString(int number, char * str, int * size);

void writeCmd(char * data, int size);

void readCtrl(unsigned char * data, int size);

int closeCtrl();

#endif
