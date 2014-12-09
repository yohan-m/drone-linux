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

#define FILE_TDOA_12 "tdoa1-2.txt"
#define FILE_TDOA_13 "tdoa1-3.txt"
#define FILE_TDOA_14 "tdoa1-4.txt"

#define FILE_TDOA_21 "tdoa2-1.txt"
#define FILE_TDOA_23 "tdoa2-3.txt"
#define FILE_TDOA_24 "tdoa2-4.txt"

#define FILE_TDOA_31 "tdoa3-1.txt"
#define FILE_TDOA_32 "tdoa3-2.txt"
#define FILE_TDOA_34 "tdoa3-4.txt"

#define FILE_TDOA_41 "tdoa4-1.txt"
#define FILE_TDOA_42 "tdoa4-2.txt"
#define FILE_TDOA_43 "tdoa4-3.txt"


typedef struct Tdoa 
{
    	float tdoa ;		/**< tdoa in s */
	float position[3];	/**< x, y, z position in m */
} Tdoa ;

Tdoa createTdoaStruct(float tdoa, float x, float y, float z) ;

void readFiles(Tdoa **arrayTdoa1, Tdoa **arrayTdoa2, Tdoa **arrayTdoa3, char * fileName1, char * fileName2, char * fileName3, int *size, int * nbX, int * nbY, int * nbZ, float * cubeSize) ;

void display(Tdoa arrayTdoa1[], Tdoa arrayTdoa2[], Tdoa arrayTdoa3[], int size) ;

#endif
