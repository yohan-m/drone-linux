/**
 * \file hyperbolic.h
 *
 * \brief hyperbolic functions
 *
 * \author Mathieu Touzery
 *
 * \date 18 Nov 2014
 */

#ifndef __HYPERBOLIC__
#define __HYPERBOLIC__

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define speedSound 360  // m/s

#define x1  0
#define y1  0
#define z1  3

#define x2  6
#define y2  0
#define z2  3

#define x3  6
#define y3  3
#define z3  3

#define x4  0
#define y4  3
#define z4  3

#define x21 x2 - x1 
#define x23 x2 - x3 
#define x31 x3 - x1 
#define x43 x4 - x3 

#define y21 y2 - y1 
#define y23 y2 - y3 
#define y31 y3 - y1 
#define y43 y4 - y3 

#define z21 z2 - z1 
#define z23 z2 - z3 
#define z31 z3 - z1 
#define z43 z4 - z3 

void computePositions(float tdoa_12, float tdoa_13, float tdoa_32, float tdoa_34, float *x, float *y, float *z) ;

#endif
