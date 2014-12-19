/**
 * \file mission.h
 *
 * \brief Regulation of the drone for the mission.
 *
 * \author Thomas Hoet
 *
 * \date 2 Dec 2014
 */

#ifndef MISSION_H
#define MISSION_H

#include <stdio.h>
#include <math.h>
#include <pthread.h>

#define PI 3.14159265

#define GAIN_PITCH 0.1
#define GAIN_ROLL 0.1
#define GAIN_ANGULAR 0.0005
#define GAIN_VERTICAL 5

void mission(float x_cons, float y_cons, float z_cons, float angle_cons, float * pitch_cmd, float * roll_cmd, float * angular_speed_cmd, float * vertical_speed_cmd);

void newNavData(float z_baro, float heading, float forward_backward_speed, float left_right_speed);
void newLocalization(float x_drone, float y_drone);

float getX();
float getY();
float getZ();
float getAngle();
void setAngleBias(float bias);

/**
 * PRIVATE
 */
 
static pthread_mutex_t mutex_mission = PTHREAD_MUTEX_INITIALIZER;
 
float x;
float y;
float z;
float angle;

float angle_bias;

int newCoordXY;
float loca_x;
float loca_y;

int newCoordZ;
float navData_z;

int newSpeed;
float navData_fb_speed;
float navData_lr_speed;

int newAngle;
float navData_angle;
 
void controller(float dx, float dy, float dz, float angle_drone_cons, float angle_drone, float * pitch_cmd, float * roll_cmd, float * angular_speed_cmd, float * vertical_speed_cmd);

void estimate_speed(float pitch_cmd, float roll_cmd, float angular_speed_cmd, float vertical_speed_cmd, float * forward_backward_speed_estimated, float * left_right_speed_estimated, float * angular_speed_estimated, float * vertical_speed_estimated);

void estimate_position(float forward_backward_speed, float left_right_speed, float angular_speed, float vertical_speed, float dt, float * x, float * y, float * z, float * angle_drone);

void room_to_drone(float dx, float dy, float angle_drone, float * pitch, float * roll);

void drone_to_room(float forward_backward_speed, float left_right_speed, float angle_drone, float * x_speed, float * y_speed);

void convert_angle(float * angle);

float diff_angle(float angle1, float angle2);

float deg_to_rad(float angle);

#endif
