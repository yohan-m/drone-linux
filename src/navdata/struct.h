#ifndef STRUCT_H
#define STRUCT_H

#include <stdint.h>

#define CVAR(a) #a  /* Using # causes the first argument after the # to be returned as a string in quotes */
#define CVARZ(a) #a
/**
 * @brief Structure for the NavData option
 */
typedef struct NavdataOption
{
  uint16_t  tag;
  uint16_t  size;

  uint8_t   data[1];

} NavdataOption ;

/**
 * @brief Structure for the NavData
 */
typedef struct Navdata
{
  uint32_t    header;                   /*!< Always set to NAVDATA_HEADER */
  uint32_t    ardrone_state;            /*!< Bit mask built from def_ardrone_state_mask_t */
  uint32_t    sequence;                 /*!< Sequence number, incremented for each sent packet */
  uint32_t    vision_defined;

  NavdataOption  options[1];

} Navdata ;

/**
 * @brief Structure for the NavData demo
 */
typedef struct NavdataDemo
{
  uint16_t    tag;					     /*!< Navdata block ('option') identifier */
  uint16_t    size;					     /*!< set this to the size of this structure */

  uint32_t    ctrl_state;                /*!< Flying state (landed, flying, hovering, etc.) defined in CTRL_STATES enum. */
  uint32_t    vbat;                      /*!< battery voltage filtered (mV) */

  float   theta;                         /*!< UAV's pitch in milli-degrees */
  float   phi;                           /*!< UAV's roll  in milli-degrees */
  float   psi;                           /*!< UAV's yaw   in milli-degrees */

  int32_t     altitude;                  /*!< UAV's altitude in centimeters */

  float   vx;                            /*!< UAV's estimated linear velocity */
  float   vy;                            /*!< UAV's estimated linear velocity */
  float   vz;                            /*!< UAV's estimated linear velocity */

} NavdataDemo ;  

#endif // STRUCT_H
