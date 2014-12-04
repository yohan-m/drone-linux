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

typedef struct Likelyhood
{
	float likelyhood ;
	float position[3] ; //en m
} Likelyhood ;

Likelyhood * createArrayLikelyhood(Tdoa *arrayTdoa1, Tdoa *arrayTdoa2, Tdoa *arrayTdoa3, int size, float tdoa1, float tdoa2, float td0a3) ;

int sortArray(Likelyhood **array, int size, int nbZ, int nbPtsPlan, float cubeSize, float realZ) ;

Likelyhood searchMin(Likelyhood *array, int size) ;

void displayArray(Tdoa *array, int size) ;

void computePosition(float *x, float *y, float *z, int tdoa1, int tdoa2, int tdoa3, int tdoa4, Tdoa *arrayTdoa1, Tdoa *arrayTdoa2, Tdoa *arrayTdoa3, int size, int nbZ, int nbPtsPlan, float cubeSize, float realZ) ;

#endif
