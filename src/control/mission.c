#include "mission.h"

void mission(float x_cons, float y_cons, float z_cons, float angle_cons, float * pitch_cmd, float * roll_cmd, float * angular_speed_cmd, float * vertical_speed_cmd)
{
	float forward_backward_speed = 0.0;
	float left_right_speed = 0.0;
	float angular_speed = 0.0;
	float vertical_speed = 0.0;	

	//Speeds
	estimate_speed(*pitch_cmd, *roll_cmd, *angular_speed_cmd, *vertical_speed_cmd, &forward_backward_speed, &left_right_speed, &angular_speed, &vertical_speed);
	
	pthread_mutex_lock(&mutex_mission);
	if(newSpeed!=0){
		forward_backward_speed = navData_fb_speed;
		left_right_speed = navData_lr_speed;
		newSpeed=0;
	}
	pthread_mutex_unlock(&mutex_mission);
	
	//Position
	estimate_position(forward_backward_speed, left_right_speed, angular_speed, vertical_speed, 0.03, &x, &y, &z, &angle);
	
	pthread_mutex_lock(&mutex_mission);
	if(newCoordXY!=0) {
		x = loca_x;
		y = loca_y;
		newCoordXY = 0;
	}
	
	if(newCoordZ!=0) {
		z = navData_z;
		newCoordZ = 0;
	}
	
	if(newAngle!=0) {
		angle = navData_angle;
		newAngle = 0;
	}

	//Errors
	float dx = x_cons - x;
	float dy = y_cons - y;
	float dz = z_cons - z;

	printf("dx=%f\tdy=%f\tdz=%f\tangle=%f\tangle_cons=%f\n",dx,dy,dz,angle,angle_cons);
	
	convert_angle(&angle);
	convert_angle(&angle_cons);
	
	//Control
	controller(dx, dy, dz, angle_cons, angle, pitch_cmd, roll_cmd, angular_speed_cmd, vertical_speed_cmd);
	pthread_mutex_unlock(&mutex_mission);
}


void newNavData(float z_baro, float heading, float forward_backward_speed, float left_right_speed)
{
	pthread_mutex_lock(&mutex_mission);
	navData_z = z_baro;
	navData_angle = heading;
	convert_angle(&navData_angle);
	navData_fb_speed = forward_backward_speed;
	navData_lr_speed = left_right_speed;
	newCoordZ = 1;
	newAngle = 1;
	newSpeed = 1;	
	pthread_mutex_unlock(&mutex_mission);
}


void newLocalization(float x_drone, float y_drone)
{
	pthread_mutex_lock(&mutex_mission);
	loca_x = x_drone;
	loca_y = y_drone;
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
	convert_angle(&angle_drone_cons);
	convert_angle(&angle_drone);
	
	room_to_drone(dx,dy,angle_drone,pitch_cmd,roll_cmd);
	
	*pitch_cmd *= -GAIN_PITCH;
	*roll_cmd  *= GAIN_ROLL;
	*angular_speed_cmd = -GAIN_ANGULAR * diff_angle(angle_drone,angle_drone_cons);
	*vertical_speed_cmd = GAIN_VERTICAL * dz;

	printf("pitch=%f\troll=%f\tangular_speed=%f\tvert_speed=%f\n",*pitch_cmd,*roll_cmd,*angular_speed_cmd,*vertical_speed_cmd);
	
	if(*pitch_cmd>1.0) {
		*pitch_cmd = 1.0;
	}
	else if(*pitch_cmd<-1.0) {
		*pitch_cmd = -1.0;
	}
	
	if(*roll_cmd>1.0) {
		*roll_cmd = 1.0;
	}
	else if(*roll_cmd<-1.0) {
		*roll_cmd = -1.0;
	}
	
	if(*angular_speed_cmd>1.0) {
		*angular_speed_cmd = 1.0;
	}
	else if(*angular_speed_cmd<-1.0) {
		*angular_speed_cmd = -1.0;
	}
	
	if(*vertical_speed_cmd>1.0) {
		*vertical_speed_cmd = 1.0;
	}
	else if(*vertical_speed_cmd<-1.0) {
		*vertical_speed_cmd = -1.0;
	}
}


void estimate_speed(float pitch_cmd, float roll_cmd, float angular_speed_cmd, float vertical_speed_cmd, float * forward_backward_speed_estimated, float * left_right_speed_estimated, float * angular_speed_estimated, float * vertical_speed_estimated)
{
	*forward_backward_speed_estimated 	= 4 * pitch_cmd;
	*left_right_speed_estimated 		= 4 * roll_cmd;
	*angular_speed_estimated 			= 180 * angular_speed_cmd;
	*vertical_speed_estimated 			= 1 * vertical_speed_cmd;
}


void estimate_position(float forward_backward_speed, float left_right_speed, float angular_speed, float vertical_speed, float dt, float * x, float * y, float * z, float * angle_drone)
{
	angular_speed *= -1;	
	forward_backward_speed *= -1;
	
	float x_speed = 0.0;
	float y_speed = 0.0;
	
	drone_to_room(forward_backward_speed, left_right_speed, *angle_drone, &x_speed, &y_speed);
	
	*x += (x_speed*dt);
	*y += (y_speed*dt);
	*z += (vertical_speed*dt);
	*angle_drone+=(angular_speed*dt);
	
	convert_angle(angle_drone);
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
