/**
 * \file navdata_manager.h
 *
 * \brief Management of the navdata on the drone (update of the mission and localization thread with last data)
 *
 * \author Yohan Marchiset
 *
 * \date 05 Dec 2014
 */

#ifndef __NAVDATA_MANAGER__
#define __NAVDATA_MANAGER__

#include "struct.h"
#include "../control/mission.h"
#include <pthread.h>

/**
 * \brief Battery level under which the drone will not take off (or will eventually crash if flying)
 */
#define LOW_BAT_LEVEL 20

/**
 * \brief Possible states of the drone (enum)
 */
typedef enum ctrl_states{
	DEFAULT = 0,	/**< Default state (unused) */
	CTRL_INIT,		/**< initialization state (when starting the drone) */
	LANDED,			/**< drone landed, ready to take off */
	FLYING,			/**< drone flying, doing some move */
	HOVERING,		/**< drone hovering over a point */
	TEST,			/**< unknown state */
	GO_TO_FIX,		/**< drone needing repair (something wrong) */
	TAKE_OFF,		/**< drone taking off (stays in this state until hovering after take off) */
	INTERMEDIATE,	/**< state reached between the end of a move and hovering state for instance */
	LANDING			/**< drone has begun landing procedure and is not yet landed */
} ctrl_states;

/**
 * \brief Necessary navdata fields to keep saved on the drone (struct)
 */
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

/**
 * \brief Last navdata received
 */
navdata_processed current_navdata;

/**
 * \brief Mutex to secure current_navdata use
 */
static pthread_mutex_t mutex_navdata = PTHREAD_MUTEX_INITIALIZER;

/**
 * \brief Initialization of the necessary fields of the manager
 */
void initNavdataManager();

/**
 * \brief Retrieves the information to fill current_navdata fields from the last NavdataDemo struct received
 * \param[in]	nd	last NavdataDemo struct received
 */
void processNavdata(NavdataDemo * nd);

/**
 * \brief Indicates whether battery is low or not
 * \return	1 if low battery, 0 otherwise
 */
int low_battery();

/**
 * \brief Getter for the latest altitude of the drone
 * \return	altitude field of current_navdata (altitude of the drone in meter)
 */
float current_altitude();

/**
 * \brief Getter for the latest psi angle of the drone
 * \return	psi field of current_navdata (orientation of the drone in degrees)
 */
float current_psi();

/**
 * \brief Getter for the latest x speed of the drone
 * \return	vx field of current_navdata (x speed of the drone in meter per second)
 */
float current_vx();

/**
 * \brief Getter for the latest y speed of the drone
 * \return	vy field of current_navdata (y speed of the drone in meter per second)
 */
float current_vy();

/**
 * \brief Updates the necessary fields of the mission thread
 */
void updateMission();

/**
 * \brief Indicates whether the drone is in a state which allows it to start a mission
 * \return	1 if it can start a mission, 0 otherwise
 */
int canStartMission();

#endif
