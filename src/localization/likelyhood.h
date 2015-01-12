/**
* \file likelyhood.h
*
* \brief likelyhood functions
*
* \author Mathieu Touzery
*
* \date 14 Oct 2014
*/

#ifndef __LIKELYHOOD__
#define __LIKELYHOOD__

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "bddTdoa.h"

/**
 * \brief Likelyhood structure
 */
typedef struct Likelyhood
{
	float likelyhood ;	/**< likelyhood value */
	float position[3] ; /** corresponding position (x,y and z in meter) */
} Likelyhood ;

/**
 * \brief Creation of a likelyhood array
 * \param[in]	arrayTdoa1	first TDOA database to use (between reference emitter and first other beacon)
 * \param[in]	arrayTdoa2	second TDOA database to use (between reference emitter and second other beacon)
 * \param[in]	arrayTdoa3	third TDOA database to use (between reference emitter and third other beacon)
 * \param[in]	size		size of the array to create
 * \param[in]	tdoa1		first tdoa value used for likelyhood value calculation
 * \param[in]	tdoa2		second tdoa value used for likelyhood value calculation
 * \param[in]	tdoa3		third tdoa value used for likelyhood value calculation
 * \param[in]	toIgnore	tdoa to ignore within the three previous parameters (farther emitter which can not be trusted)
 * \param[in]	indStart	place at which to start reading in the TDOA databases for reference values used in likelyhood value computation
 * \param[in]	indFinish	place at which to stop reading in the TDOA databases for reference values used in likelyhood value computation
 * \return		a likelyhood array
 */
Likelyhood * createArrayLikelyhood(Tdoa *arrayTdoa1, Tdoa *arrayTdoa2, Tdoa *arrayTdoa3, int size, float tdoa1, float tdoa2, float tdoa3, int toIgnore, int indStart, int indFinish) ;

/**
 * \brief Sorts the likelyhood array in order to retrieve the most likely position of the drone (unused)
 * \param[in]	array		likelyhood array to sort
 * \param[in]	size		size of the array
 * \param[in]	nbPtsPlan	nummber of points a plan contains in the test room
 * \param[in]	cubeSize	length of the side of the cubes in which the room is divided
 * \param[in]	realZ		current altitude of the drone
 * \param[in]	nbZ 
 */
int sortArray(Likelyhood **array, int size, int nbZ, int nbPtsPlan, float cubeSize, float realZ) ;

/**
 * \brief Searches for the min likelyhood value in the likelyhood array in order to retrieve the most likely position of the drone
 * \param[in]	array		likelyhood array to search
 * \param[in]	size		size of the array
 * \param[in]	nbZ			plan number the drone is closest to (0 for first plan after the ground,...)
 * \param[in]	nbPtsPlan	number of points a plan contains in the test room
 * \param[in]	cubeSize	length of the side of the cubes in which the room is divided
 * \param[in]	realZ		current altitude of the drone
 * \return		the likelyhood structure which has the minimum likelyhood value
 */
Likelyhood searchMin(Likelyhood *array, int size, int nbZ, int nbPtsPlan, float cubeSize, float realZ) ;

/**
 * \brief Displays the entire tdoa table (used for debug)
 */
void displayArray(Tdoa *array, int size) ;

/**
 * \brief Finds the current position of the drone when data is received via USB (creates and searches min in likelyhood array)
 * \param[in]	x			x position of the drone determined by the function
 * \param[in]	y			y position of the drone determined by the function
 * \param[in]	z			z position of the drone determined by the function
 * \param[in]	tabTdoa		table of the last tdoa received via USB
 * \param[in]	tabRss		table of the last rss received via USB
 * \param[in]	arrayTdoa12	database of theoretical TDOA between beacon 1 and 2
 * \param[in]	arrayTdoa13	database of theoretical TDOA between beacon 1 and 3
 * \param[in]	arrayTdoa14	database of theoretical TDOA between beacon 1 and 4
 * \param[in]	arrayTdoa21	database of theoretical TDOA between beacon 2 and 1
 * \param[in]	arrayTdoa23	database of theoretical TDOA between beacon 2 and 3
 * \param[in]	arrayTdoa24	database of theoretical TDOA between beacon 2 and 4
 * \param[in]	arrayTdoa31	database of theoretical TDOA between beacon 3 and 1
 * \param[in]	arrayTdoa32	database of theoretical TDOA between beacon 3 and 2
 * \param[in]	arrayTdoa34	database of theoretical TDOA between beacon 3 and 4
 * \param[in]	arrayTdoa41	database of theoretical TDOA between beacon 4 and 1
 * \param[in]	arrayTdoa42	database of theoretical TDOA between beacon 4 and 2
 * \param[in]	arrayTdoa43	database of theoretical TDOA between beacon 4 and 3
 * \param[in]	size		size of the array
 * \param[in]	nbPtsPlan	nummber of points a plan contains in the test room
 * \param[in]	cubeSize	length of the side of the cubes in which the room is divided
 * \param[in]	realZ		current altitude of the drone
 * \param[in]	nbZ
 */
void computePosition(float *x, float *y, float *z, float * tabTdoa, int32_t * tabRss, Tdoa *arrayTdoa12, Tdoa *arrayTdoa13, Tdoa *arrayTdoa14, Tdoa *arrayTdoa21, Tdoa *arrayTdoa23, Tdoa *arrayTdoa24, Tdoa *arrayTdoa31, Tdoa *arrayTdoa32, Tdoa *arrayTdoa34, Tdoa *arrayTdoa41, Tdoa *arrayTdoa42, Tdoa *arrayTdoa43, int size, int nbZ, int nbPtsPlan, float cubeSize, float realZ) ;

#endif
