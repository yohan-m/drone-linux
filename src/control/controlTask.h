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
#include "../navdata/navdata_manager.h"
#include "../udp/udp_protocol.h"

/**
 * \brief State of the control task : manual (drone controled by the user).
 */
#define STATE_MANUAL 0

/**
 * \brief State of the control task : mission (the drone control itself).
 */
#define STATE_MISSION 1

/**
 * \brief The control taks is running.
 */
#define CONTROL_ENABLED 0

/**
 * \brief The control taks is not running.
 */
#define CONTROL_DISABLED 1

/**
 * \brief Precision to determine the end of the mission (m).
 */
#define PRECISION_X (float)0.5	

/**
 * \brief Precision to determine the end of the mission (m).
 */
#define PRECISION_Y (float)0.5	

/**
 * \brief Precision to determine the end of the mission (m).
 */ 
#define PRECISION_Z (float)0.2	

/**
 * \brief Precision to determine the end of the mission (m).
 */
#define PRECISION_ANGLE (float)10.0

/**
 * \brief Amplitude of the movement (right/left/forward/backward).
 */
#define MOVE_AMPLITUDE 0.4

/**
 * \brief Amplitude of the movement (vertical and angular speed).
 */
#define SPEED_AMPLITUDE 0.6

/**
 * \brief Period of the control task (ms).
 */
#define CONTROLTASK_PERIOD_MS 30

/**
 * \brief Control task. This task manages le movement of the drone.
 * \param[in]	arg
 */
void *controlTask(void *arg);

/**
 * \brief Start a mission with a specified objective. Set the state of the task to mission.
 * \param[in]	x_obj		Objective (X)
 * \param[in]	y_obj		Objective (Y)
 * \param[in]	z_obj		Objective (Z)
 * \param[in]	angle_obj	Objective (Angle)
 */
int executeMission(float x_obj, float y_obj, float z_obj, float angle_obj);

/**
 * \brief Set the state of the task to manual : the drone is controled by the user.
 */
void executeManual();

/**
 * \brief Enable or disable the control task on the drone.
 * \param[in]	enable CONTROL_ENABLED or CONTROL_DISABLED
 */
void enableControl(int enable);

/**
 * \brief Initialize the reception of navData.
 */
void initNavData();

/**
 * \brief The drone takes off.
 */
void takeOff();

/**
 * \brief The drone lands.
 */
void land();

/**
 * \brief Move the drone 
 * \param[in]	pitch
 * \param[in]	roll
 * \param[in]	angular_speed
 * \param[in]	vertical_speed
 */
void move(float pitch, float roll, float angular_speed, float vertical_speed);

/**
 * \brief Calibrate the horizontal plane of the drone (must be landed).
 */
void calibHor();

/**
 * \brief Calibrate the magnetometer of the drone (must be flying).
 */
void calibMagn();

/**
 * \brief Leave the emergency mode (red leds).
 */
void emergency();

/**
 * PRIVATE
 */
 
/**
 * \brief Check the end of the mission (if the objective is reached).
 */
void checkEndOfMission();
 
/**
 * \brief Mutex to protect the control task data.
 */
static pthread_mutex_t mutex_control = PTHREAD_MUTEX_INITIALIZER;


int control_enable;
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
