#include "controlTask.h"

void *controlTask(void *arg)
{
	struct timeval tp;
    struct timespec ts;	
	pthread_mutex_t verrou; 
	pthread_cond_t cond; 	
	pthread_cond_init(&cond, NULL); 
    pthread_mutex_init(&verrou, NULL);
        
	float pitch_cmd = 0.0;
	float roll_cmd = 0.0;
	float angular_speed_cmd = 0.0;
	float vertical_speed_cmd = 0.0;	
	
	initControl();
	
	pthread_mutex_lock(&mutex_control);
	control_enable = CONTROL_ENABLED;
	control_state = STATE_MANUAL;
	seqNumber = 0;
	takeOffCalled = 0;
	landCalled = 0;
	moveCalled = 0;
	emergencyCalled = 0;
	calibHorCalled = 0;
	calibMagnCalled = 0;
	initNavDataCalled = 0;
	move_done = 0;
	pthread_mutex_unlock(&mutex_control);
	
	while(1) {   		
   		gettimeofday(&tp, NULL);
   		ts.tv_sec = tp.tv_sec;
     	ts.tv_nsec = tp.tv_usec * 1000;
     	ts.tv_nsec += CONTROLTASK_PERIOD_MS * 1000000;
     	ts.tv_sec += ts.tv_nsec / 1000000000L;
     	ts.tv_nsec = ts.tv_nsec % 1000000000L;
		pthread_mutex_lock(&verrou);
		
		pthread_mutex_lock(&mutex_control);
		
		if(control_enable == CONTROL_ENABLED) {
		
			if(control_state == STATE_MISSION) {
				mission(x_cons, y_cons, z_cons, angle_cons, &pitch_cmd, &roll_cmd, &angular_speed_cmd, &vertical_speed_cmd);
				sendMovement(seqNumber, 1, pitch_cmd, roll_cmd, vertical_speed_cmd, angular_speed_cmd);
				checkEndOfMission();
				printf("x=%f\ty=%f\tz=%f\tangle=%f\t\tpitch=%f\troll=%f\taspeed=%f\tvspeed=%f\n",getX(),getY(),getZ(),getAngle(),pitch_cmd,roll_cmd,angular_speed_cmd,vertical_speed_cmd);
			}
		
			else if(control_state == STATE_MANUAL) {
		
				if(landCalled==1) {
					sendLand(seqNumber);
					landCalled = 0;
				}
				else if(takeOffCalled==1) {
					sendTakeOff(seqNumber);
					takeOffCalled = 0;
				}
				else if(initNavDataCalled==1) {
					sendNavDataInit(seqNumber);
					initNavDataCalled = 0;
				}
				else if(moveCalled==1) {
					sendMovement(seqNumber, 1, pitch_move, roll_move, vertical_speed_move, angular_speed_move);
					move_done = 1;
					moveCalled = 0;
				}
				else if(emergencyCalled==1) {
					sendEmergency(seqNumber);
					emergencyCalled = 0;
				}
				else if(calibHorCalled==1) {
					sendCalibHPlan(seqNumber);
					calibHorCalled = 0;
				}
				else if(calibMagnCalled==1) {
					sendCalibMagn(seqNumber);
					calibMagnCalled = 0;
				}
				else if(move_done==1) {
					sendMovement(seqNumber,0,0.0,0.0,0.0,0);
					move_done = 0;
				}
				else {
					sendResetWatchdog(seqNumber);
				}
			}
			seqNumber++;
		
		}
		
		pthread_mutex_unlock(&mutex_control);
		
    	pthread_cond_timedwait(&cond, &verrou, &ts); 
    	pthread_mutex_unlock(&verrou); 				
	}	
}


int executeMission(float x_obj, float y_obj, float z_obj, float angle_obj)
{
	if(!canStartMission()) {
		return -1;
	}
	pthread_mutex_lock(&mutex_control);
	x_cons = x_obj;
	y_cons = y_obj;
	z_cons = z_obj;
	angle_cons = angle_obj;
	control_state = STATE_MISSION;
	pthread_mutex_unlock(&mutex_control);
	return 0;
}


void executeManual()
{		
	pthread_mutex_lock(&mutex_control);
	takeOffCalled = 0;
	landCalled = 0;
	moveCalled = 0;
	emergencyCalled = 0;
	calibHorCalled = 0;
	calibMagnCalled = 0;
	control_state = STATE_MANUAL;
	pthread_mutex_unlock(&mutex_control);
}


void enableControl(int enable) 
{
	pthread_mutex_lock(&mutex_control);
	if(enable==CONTROL_ENABLED || enable==CONTROL_DISABLED) {
		control_enable = enable;
	}
	control_state = STATE_MANUAL;
	seqNumber = 0;
	takeOffCalled = 0;
	landCalled = 0;
	moveCalled = 0;
	emergencyCalled = 0;
	calibHorCalled = 0;
	calibMagnCalled = 0;
	initNavDataCalled = 0;
	move_done = 0;
	pthread_mutex_unlock(&mutex_control);
}


void initNavData()
{
	pthread_mutex_lock(&mutex_control);
	initNavDataCalled = 1; 
	pthread_mutex_unlock(&mutex_control);
}


void takeOff() 
{
	pthread_mutex_lock(&mutex_control);
	takeOffCalled = 1;
	pthread_mutex_unlock(&mutex_control);
}


void land() 
{
	pthread_mutex_lock(&mutex_control);
	landCalled = 1;
	pthread_mutex_unlock(&mutex_control);
}


void move(float pitch, float roll, float angular_speed, float vertical_speed) 
{
	pthread_mutex_lock(&mutex_control);
	pitch_move = pitch;
	roll_move = roll;
	angular_speed_move = angular_speed;
	vertical_speed_move = vertical_speed;
	moveCalled = 1;
	pthread_mutex_unlock(&mutex_control);
}


void calibHor() 
{
	pthread_mutex_lock(&mutex_control);
	calibHorCalled = 1;
	pthread_mutex_unlock(&mutex_control);
}


void calibMagn()
{
	pthread_mutex_lock(&mutex_control);
	calibMagnCalled = 1;
	pthread_mutex_unlock(&mutex_control);
}


void emergency()
{
	pthread_mutex_lock(&mutex_control);
	emergencyCalled = 1;
	pthread_mutex_unlock(&mutex_control);
}


/*****************************/
/**         PRIVATE         **/
/*****************************/


void checkEndOfMission()
{
	if( fabs(x_cons-getX()) < PRECISION_X && fabs(y_cons-getY()) < PRECISION_Y && fabs(z_cons-getZ()) < PRECISION_Z && fabs(diff_angle(angle_cons, getAngle())) < PRECISION_ANGLE ) {
		move_done = 1;
		executeManual();
	}
}

