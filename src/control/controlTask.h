/**
 * \file controlTask.h
 *
 * \brief Control the drone, send a frame each 30ms.
 *
 * \author Thomas Hoet
 *
 * \date 3 Dec 2014
 */
 
#ifndef CONTROLTASK_H
#define CONTROLTASK_H

#include <unistd.h>
#include <math.h>

#include <time.h>
#include <pthread.h>

#include "mission.h"
#include "control.h"

#define STATE_MANUAL 0
#define STATE_MISSION 1

#define PRECISION_X (float)0.2 		//m
#define PRECISION_Y (float)0.2	 	//m
#define PRECISION_Z (float)0.1 		//m
#define PRECISION_ANGLE (float)10.0 //degrees

#define CONTROLTASK_PERIOD_MS 30

void *controlTask(void *arg);
void executeMission(float x_obj, float y_obj, float z_obj, float angle_obj);
void executeManual();

void initNavData();
void takeOff();
void land();
void move(float pitch, float roll, float angular_speed, float vertical_speed);
void calibHor();
void calibMagn();
void emergency();

/**
 * PRIVATE
 */
 
void checkEndOfMission();

int control_state;
int seqNumber;
float x_cons;
float y_cons;
float z_cons;
float angle_cons;

int takeOffCalled;
int initNavDataCalled;
int landCalled;
int moveCalled;
int emergencyCalled;
int calibHorCalled;
int calibMagnCalled;
int move_done;

float pitch_move;
float roll_move;
float angular_speed_move;
float vertical_speed_move;

#endif
