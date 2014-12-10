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

Likelyhood * createArrayLikelyhood(Tdoa *arrayTdoa1, Tdoa *arrayTdoa2, Tdoa *arrayTdoa3, int size, float tdoa1, float tdoa2, float td0a3, int toIgnore, int indStart, int indFinish) ;

int sortArray(Likelyhood **array, int size, int nbZ, int nbPtsPlan, float cubeSize, float realZ) ;

Likelyhood searchMin(Likelyhood *array, int size, int nbZ, int nbPtsPlan, float cubeSize, float realZ) ;

void displayArray(Tdoa *array, int size) ;

void computePosition(float *x, float *y, float *z, int32_t * tabTdoa, int32_t * tabRss, Tdoa *arrayTdoa12, Tdoa *arrayTdoa13, Tdoa *arrayTdoa14, Tdoa *arrayTdoa21, Tdoa *arrayTdoa23, Tdoa *arrayTdoa24, Tdoa *arrayTdoa31, Tdoa *arrayTdoa32, Tdoa *arrayTdoa34, Tdoa *arrayTdoa41, Tdoa *arrayTdoa42, Tdoa *arrayTdoa43, int size, int nbZ, int nbPtsPlan, float cubeSize, float realZ) ;

#endif
