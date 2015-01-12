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
#include "../../../common-sources/src/defines.h"

#define PI 3.14159265

/**
 * \brief Gain applied on the pitch command
 */
#define GAIN_PITCH 0.1

/**
 * \brief Gain applied on the roll command
 */
#define GAIN_ROLL 0.1

/**
 * \brief Gain applied on the angular command
 */
#define GAIN_ANGULAR 0.0005

/**
 * \brief Gain applied on the vertical command
 */
#define GAIN_VERTICAL 5


/**
 * \brief Saturation of the pitch command
 */
#define PITCH_CMD_MAX 0.08

/**
 * \brief Saturation of the roll command
 */
#define ROLL_CMD_MAX 0.08

/**
 * \brief Saturation of the angular command
 */
#define ANGULAR_CMD_MAX 0.3

/**
 * \brief Saturation of the vertical command
 */
#define VERTICAL_CMD_MAX 0.4

/**
 * \brief Calculate the command of the drone in order to move the drone to a specific point.
 * The controler use the state of the drone x,y,z and the angle, you must refresh it periodically 
 * (see newLocalization() and newNavData()).
 * \param[in]    x_cons 			Desired X
 * \param[in]	 y_cons 			Desired Y
 * \param[in]	 z_cons 			Desired Z
 * \param[in]	 angle_cons			Desired angle
 * \param[out]	 pitch_cmd			Pitch command
 * \param[out]	 roll_cmd		    Roll command
 * \param[out]	 angular_speed_cmd  Angular speed command
 * \param[out]	 vertical_speed_cmd	Vertical speed command
 */
void mission(float x_cons, float y_cons, float z_cons, float angle_cons, float * pitch_cmd, float * roll_cmd, float * angular_speed_cmd, float * vertical_speed_cmd);

/**
 * \brief Call this function to refresh the state of the drone using by the controller.
 * \param[in]	 z_baro					Value of the barometer (meters)
 * \param[in]	 heading				Value of the yaw (angle of the drone)
 * \param[in]	 forward_backward_speed	Value of the forward/backward speed of the drone (not used in this version)
 * \param[in]	 left_right_speed		Value of the left/right speed of the drone (not used in this version)
 */
void newNavData(float z_baro, float heading, float forward_backward_speed, float left_right_speed);

/**
 * \brief Call this function to refresh the state of the drone using by the controller.
 * \param[in]	 x_drone		Coordinate X of the drone.
 * \param[in]	 y_drone		Coordinate Y of the drone.
 */
void newLocalization(float x_drone, float y_drone);

/**
 * \brief Get the current value of the coordinate X.
 */
float getX();

/**
 * \brief Get the current value of the coordinate Y.
 */
float getY();

/**
 * \brief Get the current value of the coordinate Z.
 */
float getZ();

/**
 * \brief Get the current value of the angle.
 */
float getAngle();

/**
 * PRIVATE
 */

/**
 *  \brief This function calculate the command of the drone using the errors.
 *  \param[in]	 dx					Difference between the current X and the objective
 *  \param[in]	 dy					Difference between the current Y and the objective
 *  \param[in]	 dz					Difference between the current Z and the objective
 *  \param[in]	 angle_drone_cons	Objective of the drone (angle)
 *  \param[in]	 angle_drone		Current angle of the drone
 *  \param[out]	 pitch_cmd			Pitch command
 *  \param[out]	 roll_cmd			Roll command
 *  \param[out]	 angular_speed_cmd	Angular speed command
 *  \param[out]	 vertical_speed_cmd	Vertical speed command
 */
void controller(float dx, float dy, float dz, float angle_drone_cons, float angle_drone, float * pitch_cmd, float * roll_cmd, float * angular_speed_cmd, float * vertical_speed_cmd);

/**
 * \brief Change of reference : from the room coordinates to the drone coordinates.
 * \param[in] 	dx				Difference between the current X and the objective
 * \param[in] 	dy				Difference between the current Y and the objective
 * \param[in] 	angle_drone		Current angle of the drone
 * \param[out]  pitch			Projection of dx,dy on the pitch coordinate
 * \param[out] 	roll			Projection of dx,dy on the roll coordinate
 */
void room_to_drone(float dx, float dy, float angle_drone, float * pitch, float * roll);

/**
 * \brief Change of reference : from the drone coordinates to the drone coordinates room coordinates.
 * \param[in] 	forward_backward_speed	Current value of the forward/backward speed
 * \param[in] 	left_right_speed		Current value of the left/right speed
 * \param[in] 	angle_drone				Current angle of the drone
 * \param[out]  x_speed					Projection on the X coordinate
 * \param[out] 	y_speed					Projection on the Y coordinate
 */
void drone_to_room(float forward_backward_speed, float left_right_speed, float angle_drone, float * x_speed, float * y_speed);

/**
 * \brief Return the angle between +180 and -180°.
 * \param[in] 	angle	Angle to convert (°).
 */
void convert_angle(float * angle);

/**
 * \brief Return the difference between the angle2 and the angle1 (between +180 and 180°).
 * \param[in]	angle1
 * \param[in]	angle2
 * \return the difference between the 2 angles (between +180 and -180°).
 */
float diff_angle(float angle1, float angle2);

/**
 * \brief Convert an angle (degree -> radian).
 * \param[in]	angleToRad
 * \return 		angle in radian.
 */
float deg_to_rad(float angleToRad);
 
/**
 * \brief Mutex for the protection of the data.
 */
static pthread_mutex_t mutex_mission = PTHREAD_MUTEX_INITIALIZER;
 
/**
 * \brief Coordinate X.
 */ 
float x;
 
/**
 * \brief Coordinate Y.
 */ 
float y;
 
/**
 * \brief Coordinate Z.
 */ 
float z;
 
/**
 * \brief Angle of the drone.
 */ 
float angle;
 
/**
 * \brief Variable to indicate that new data are available.
 */ 
int newCoordXY;
 
/**
 * \brief Variable to indicate that new data are available.
 */ 
int newCoordZ;

/**
 * \brief Variable to indicate that new data are available.
 */ 
int newSpeed;

/**
 * \brief Variable to indicate that new data are available.
 */ 
int newAngle;

/**
 * \brief Variable that contains the new X value.
 */
float loca_x;

/**
 * \brief Variable that contains the new Y value.
 */
float loca_y;

/**
 * \brief Variable that contains the new Z value.
 */
float navData_z;

/**
 * \brief Variable that contains the new forward/backward speed value.
 */
float navData_fb_speed;

/**
 * \brief Variable that contains the new left/right speed value.
 */
float navData_lr_speed;

/**
 * \brief Variable that contains the new angle value.
 */
float navData_angle;

#endif
