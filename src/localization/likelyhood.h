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
	float position[3] ;
} Likelyhood ;


Likelyhood * createArrayLikelyhood(Tdoa *arrayTdoa1, Tdoa *arrayTdoa2, Tdoa *arrayTdoa3, int size, float tdoa1, float tdoa2, float td0a3) ;

void sortArray(Likelyhood **array, int size) ;

void displayArray(Likelyhood *array, int size) ;


#endif
