/**
 * \file bddTdoa.h
 *
 * \brief DataBase of Theorical Tdoas
 *
 * \author Mathieu Touzery
 *
 * \date 07 Oct 2014
 */

#ifndef __TDOA__
#define __TDOA__

#include <stdio.h>
#include <stdint.h>

typedef struct Tdoa 
{
    	float tdoa ;		/**< tdoa in s */
	float position[3];	/**< x, y, z position in m */
} Tdoa ;

Tdoa createTdoaStruct(float tdoa, float x, float y, float z) ;

void readFiles(Tdoa **arrayTdoa1, Tdoa **arrayTdoa2, Tdoa **arrayTdoa3, int *size) ;

void display(Tdoa arrayTdoa1[], Tdoa arrayTdoa2[], Tdoa arrayTdoa3[], int size) ;

#endif
