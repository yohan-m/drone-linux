/**
 * \file leds_motors_manager.h
 *
 * \brief Functions to control the leds and the motors of the drone.
 *
 * \author Thomas Hoet
 *
 * \date 12 Oct 2014
 */

#ifndef LEDS_MOTORS_MANAGER_H
#define LEDS_MOTORS_MANAGER_H

#include "leds_motors_driver.h"

#define PERIOD_MOTOR_US 5000
#define FREQUENCY_MOTOR_HZ 200

/**
 * \brief possible state for the leds.
 */
enum color {GREEN,ORANGE,RED,OFF};

/**
 * \brief Initialize the driver.
 * \details It must be called one time before any other functions of this file.
 */
int leds_motors_init();

/**
 * \brief Close the driver.
 */
int leds_motors_close();

/**
 * \brief Set the color of the leds.
 */
int set_leds(enum color led1, enum color led2, enum color led3, enum color led4);

/**
 * \brief Set all the leds green.
 */
int set_leds_green();

/**
 * \brief Set all the leds orange.
 */
int set_leds_orange();

/**
 * \brief Set all the leds red.
 */
int set_leds_red();

/**
 * \brief Switch off all the leds.
 */
int set_leds_off();

/**
 * \brief Set each motors pwm, from 0(min) to 511(max).
 */
int set_motors(int pwm1, int pwm2, int pwm3, int pwm4);

/**
 * \brief Set the same pwm to each motors, from 0(min) to 511(max).
 */
int set_all_motors(int pwm);

#endif
