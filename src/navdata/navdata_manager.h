#ifndef __NAVDATA_MANAGER__
#define __NAVDATA_MANAGER__

#include "struct.h"
#include <pthread.h>

#define LOW_BAT_LEVEL 20

typedef enum ctrl_states{
	DEFAULT = 0,
	CTRL_INIT,
	LANDED,
	FLYING,
	HOVERING,
	TEST,
	GO_TO_FIX,
	TAKE_OFF,
	INTERMEDIATE,
	LANDING
} ctrl_states;

typedef struct navdata_processed{
	ctrl_states state;		/*!< state of the drone */
	uint32_t    bat;       /*!< battery percentage */

	float   theta;          /*!< UAV's pitch in degrees */
	float   phi;            /*!< UAV's roll  in degrees */
	float   psi;            /*!< UAV's yaw   in degrees */

	float     altitude;     /*!< UAV's altitude in meters */

	float   vx;             /*!< UAV's estimated linear velocity in m/s */
	float   vy;             /*!< UAV's estimated linear velocity in m/s */
} navdata_processed;

navdata_processed current_navdata;

static pthread_mutex_t mutex_navdata = PTHREAD_MUTEX_INITIALIZER;

void initNavdataManager();

void processNavdata(NavdataDemo * nd);

int low_battery();

float current_altitude();

float current_psi();

float current_vx();

float current_vy();

#endif
