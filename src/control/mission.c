#include "mission.h"

void mission(float x_cons, float y_cons, float z_cons, float angle_cons, float * pitch_cmd, float * roll_cmd, float * angular_speed_cmd, float * vertical_speed_cmd)
{
	pthread_mutex_lock(&mutex_mission);
	
	// Refresh X and Y if new data are available
	if(newCoordXY!=0) {
		x = loca_x;
		y = loca_y;
		newCoordXY = 0;
	}
	
	// Refresh Z if new data are available
	if(newCoordZ!=0) {
		z = navData_z;
		newCoordZ = 0;
	}
	
	// Refresh the heading if new data is available
	if(newAngle!=0) {
		angle = navData_angle;
		newAngle = 0;
	}

	// Calculate the error (input of the controller)
	float dx = x_cons - x;
	float dy = y_cons - y;
	float dz = z_cons - z;
	
	// Convert the angle in order that it is between -180 and +180°
	convert_angle(&angle);
	convert_angle(&angle_cons);
	
	//printf("dx=%f\tdy=%f\tdz=%f\tangle=%f\tangle_cons=%f\n",dx,dy,dz,angle,angle_cons);	
	
	// Calculate the command (output of the controller / input of the drone)
	controller(dx, dy, dz, angle_cons, angle, pitch_cmd, roll_cmd, angular_speed_cmd, vertical_speed_cmd);
	
	pthread_mutex_unlock(&mutex_mission);
}


void newNavData(float z_baro, float heading, float forward_backward_speed, float left_right_speed)
{
	pthread_mutex_lock(&mutex_mission);
	
	// Save the new data
	navData_z = z_baro;
	navData_angle = heading-BIAIS;
	convert_angle(&navData_angle);
	navData_fb_speed = forward_backward_speed;
	navData_lr_speed = left_right_speed;
	
	// Indicate that new data are available
	newCoordZ = 1;
	newAngle = 1;
	newSpeed = 1;	
	
	pthread_mutex_unlock(&mutex_mission);
}


void newLocalization(float x_drone, float y_drone)
{
	pthread_mutex_lock(&mutex_mission);
	
	// Save the new data
	loca_x = x_drone;
	loca_y = y_drone;
	
	// Indicate that new data is available
	newCoordXY = 1;
	
	pthread_mutex_unlock(&mutex_mission);
}

float getX()
{
	pthread_mutex_lock(&mutex_mission);
	float x_local = x ;
	pthread_mutex_unlock(&mutex_mission);
	return x_local;
}

float getY()
{
	pthread_mutex_lock(&mutex_mission);
	float y_local = y ;
	pthread_mutex_unlock(&mutex_mission);
	return y_local;
}

float getZ()
{
	pthread_mutex_lock(&mutex_mission);
	float z_local = z ;
	pthread_mutex_unlock(&mutex_mission);
	return z_local;
}

float getAngle()
{
	pthread_mutex_lock(&mutex_mission);
	float angle_local = angle ;
	pthread_mutex_unlock(&mutex_mission);
	return angle_local;
}


/*****************************/
/**         PRIVATE         **/
/*****************************/

void controller(float dx, float dy, float dz, float angle_drone_cons, float angle_drone, float * pitch_cmd, float * roll_cmd, float * angular_speed_cmd, float * vertical_speed_cmd)
{
	// Angle must be between -180 and +180°
	convert_angle(&angle_drone_cons);
	convert_angle(&angle_drone);
	
	// CHange of reference (from the room reference to the drone reference)
	room_to_drone(dx,dy,angle_drone,pitch_cmd,roll_cmd);
	
	// Apply gain
	*pitch_cmd *= -GAIN_PITCH;
	*roll_cmd  *= GAIN_ROLL;
	*angular_speed_cmd = -GAIN_ANGULAR * diff_angle(angle_drone,angle_drone_cons);
	*vertical_speed_cmd = GAIN_VERTICAL * dz;

	//printf("pitch=%f\troll=%f\tangular_speed=%f\tvert_speed=%f\n",*pitch_cmd,*roll_cmd,*angular_speed_cmd,*vertical_speed_cmd);
	
	// Saturate the command if necessary
	if(*pitch_cmd>PITCH_CMD_MAX) {
		*pitch_cmd = PITCH_CMD_MAX;
	}
	else if(*pitch_cmd<-PITCH_CMD_MAX) {
		*pitch_cmd = -PITCH_CMD_MAX;
	}
	
	if(*roll_cmd>ROLL_CMD_MAX) {
		*roll_cmd = ROLL_CMD_MAX;
	}
	else if(*roll_cmd<-ROLL_CMD_MAX) {
		*roll_cmd = -ROLL_CMD_MAX;
	}
		
	if(*angular_speed_cmd>ANGULAR_CMD_MAX) {
		*angular_speed_cmd = ANGULAR_CMD_MAX;
	}
	else if(*angular_speed_cmd<-ANGULAR_CMD_MAX) {
		*angular_speed_cmd = -ANGULAR_CMD_MAX;
	}
	
	if(*vertical_speed_cmd>VERTICAL_CMD_MAX) {
		*vertical_speed_cmd = VERTICAL_CMD_MAX;
	}
	else if(*vertical_speed_cmd<-VERTICAL_CMD_MAX) {
		*vertical_speed_cmd = -VERTICAL_CMD_MAX;
	}
}


void drone_to_room(float forward_backward_speed, float left_right_speed, float angle_drone, float * x_speed, float * y_speed)
{
	*x_speed = forward_backward_speed * sinf(deg_to_rad(angle_drone)) - left_right_speed * cosf(deg_to_rad(angle_drone));
	*y_speed = forward_backward_speed * cosf(deg_to_rad(angle_drone)) + left_right_speed * sinf(deg_to_rad(angle_drone));
}


void room_to_drone(float dx, float dy, float angle_drone, float * pitch, float * roll)
{
	*pitch = dy * cosf(deg_to_rad(angle_drone)) + dx * sinf(deg_to_rad(angle_drone));	
	*roll  = dy * sinf(deg_to_rad(angle_drone)) - dx * cosf(deg_to_rad(angle_drone));
}


void convert_angle(float * angleToConvert)
{
	while(*angleToConvert>180.0 || *angleToConvert<-180.0 ) {
		if(*angleToConvert>180.0) {
			*angleToConvert -= 360.0;
		}
		else if(*angleToConvert<-180.0) {
			*angleToConvert += 360.0;
		}
	}
}


float diff_angle(float angle1, float angle2)
{
	float diff;
	diff = angle2-angle1;
	convert_angle(&diff);
	
	return diff;
}


float deg_to_rad(float angleToRad)
{
	return (angleToRad*PI/180.0);
}
