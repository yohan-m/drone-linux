#include "navdata_manager.h"

void initNavdataManager(){
	// critical section
	pthread_mutex_lock(&mutex_navdata);
	current_navdata.state = DEFAULT;
	current_navdata.bat = 0;
	current_navdata.theta = 0.0;
	current_navdata.phi = 0.0;
	current_navdata.psi = 0.0;
	current_navdata.altitude = 0.0;
	current_navdata.vx = 0.0;
	current_navdata.vy = 0.0;
	pthread_mutex_unlock(&mutex_navdata);
	// end of critical section
}

void processNavdata(NavdataDemo * nd){
	// critical section
	pthread_mutex_lock(&mutex_navdata);
	int state = (nd->ctrl_state) >> 16;
	if(state<10){
		current_navdata.state = state;
	}
	else{
		current_navdata.state = DEFAULT;
	}
	current_navdata.bat = nd->vbat;
	current_navdata.theta = nd->theta/1000.0;
	current_navdata.phi = nd->phi/1000.0;
	current_navdata.psi = nd->psi/1000.0;
	current_navdata.altitude = (float)nd->altitude/1000.0;
	current_navdata.vx = nd->vx/1000.0;
	current_navdata.vy = nd->vy/1000.0;
	pthread_mutex_unlock(&mutex_navdata);
	// end of critical section
}

int low_battery(){
	// critical section
	pthread_mutex_lock(&mutex_navdata);
	int bat_level = current_navdata.bat;
	pthread_mutex_unlock(&mutex_navdata);
	// end of critical section
	if(bat_level<=LOW_BAT_LEVEL){
		return 1;
	}
	else{
		return 0;
	}
}

float current_altitude(){
	// critical section
	pthread_mutex_lock(&mutex_navdata);
	float altitude = current_navdata.altitude;
	pthread_mutex_unlock(&mutex_navdata);
	// end of critical section
	return altitude;
}

float current_psi(){
	// critical section
	pthread_mutex_lock(&mutex_navdata);
	float psi = current_navdata.psi;
	pthread_mutex_unlock(&mutex_navdata);
	// end of critical section
	return psi;
}

float current_vx(){
	// critical section
	pthread_mutex_lock(&mutex_navdata);
	float vx = current_navdata.vx;
	pthread_mutex_unlock(&mutex_navdata);
	// end of critical section
	return vx;
}

float current_vy(){
	// critical section
	pthread_mutex_lock(&mutex_navdata);
	float vy = current_navdata.vy;
	pthread_mutex_unlock(&mutex_navdata);
	// end of critical section
	return vy;
}

void updateMission(){
	newNavData(current_altitude(),current_psi(),-current_vx(),current_vy());
}

int canStartMission(){
	// critical section
	pthread_mutex_lock(&mutex_navdata);
	int bat = current_navdata.bat;
	ctrl_states state = current_navdata.state;
	pthread_mutex_unlock(&mutex_navdata);
	// end of critical section
	if (bat>LOW_BAT_LEVEL && (state==FLYING || state==HOVERING || state==INTERMEDIATE)){
		return 1;
	}
	else{
		return 0;
	}
}

