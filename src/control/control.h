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

void initControl();

void sendNavDataInit(int seqNum);

void sendResetWatchdog(int seqNum);

void sendEmergency(int seqNum);

void sendCalibHPlan(int seqNum);

void sendCalibMagn(int seqNum);

void sendTakeOff(int seqNum);

void sendLand(int seqNum);

void sendMovement(int seqNum, int flag, float leftRightTilt, float frontBackTilt, float verticalSpeed, float angularSpeed);

void numberToString(int number, char * str, int * size);

void writeCmd(char * data, int size);

#endif
