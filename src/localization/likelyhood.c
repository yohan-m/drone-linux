#include "likelyhood.h"

Likelyhood * createArrayLikelyhood(Tdoa *arrayTdoa1, Tdoa *arrayTdoa2, Tdoa *arrayTdoa3, int size, float tdoa1, float tdoa2, float tdoa3)
{
	Likelyhood* arrayLikelyhood = (Likelyhood*)malloc(sizeof(Likelyhood)*size) ;

	int i ;
	for (i = 0 ; i<size ; i++)
	{
		arrayLikelyhood[i].likelyhood = fabs(arrayTdoa1[i].tdoa - tdoa1) + fabs(arrayTdoa2[i].tdoa - tdoa2) + fabs(arrayTdoa3[i].tdoa - tdoa3) ;
		arrayLikelyhood[i].position[0] = arrayTdoa1[i].position[0] ;
		arrayLikelyhood[i].position[1] = arrayTdoa1[i].position[1] ;
		arrayLikelyhood[i].position[2] = arrayTdoa1[i].position[2] ;
	}

	return arrayLikelyhood ;
}


void sortArray(Likelyhood **array, int size)
{
	int i ;
	Likelyhood temp ;
	int sorted = 0 ;

	while (!sorted)
	{
		sorted = 1 ;

		for(i = 0 ; i<size-1 ; i++)
		{
			if ((*array)[i].likelyhood > (*array)[i+1].likelyhood)
			{
				temp = (*array)[i] ;
				(*array)[i] = (*array)[i+1] ;
				(*array)[i+1] = temp ;
				sorted = 0 ;
			}	
		}
	}
}

Likelyhood searchMin(Likelyhood *array, int size)
{
	int i = 0, indMin = 0 ;
	float min = 1000.0 ;
	Likelyhood likelyhood ;

	for(i = 0 ; i<size ; i++)
	{
		if(array[i].likelyhood < min)
		{
			min = array[i].likelyhood ;
			indMin = i ;
		}
	}

	return array[indMin] ;
}

void displayArray(Tdoa *array, int size)
{
	int i = 0 ;
	for(i = 0 ; i<size ; i++)
	{
		printf("%f %f %f %f\n", array[i].tdoa, array[i].position[0], array[i].position[1], array[i].position[2]) ;
	}
}

void computePosition(float *x, float *y, float *z, int tdoa1, int tdoa2, int tdoa3, int tdoa4, Tdoa *arrayTdoa1, Tdoa *arrayTdoa2, Tdoa *arrayTdoa3, int size)
{
	float tdoa12 = 0.0, tdoa13 = 0.0, tdoa14 = 0.0 ;
	Likelyhood *arrayLikelyhood = NULL ;

	tdoa12 = (float)(tdoa2 - tdoa1) * 1.0/128.0;
	tdoa13 = (float)(tdoa3 - tdoa1) * 1.0/128.0;
	tdoa14 = (float)(tdoa4 - tdoa1) * 1.0/128.0;

	//displayArray(arrayTdoa1, size) ;

	arrayLikelyhood = createArrayLikelyhood(arrayTdoa1, arrayTdoa2, arrayTdoa3, size, tdoa12, tdoa13, tdoa14) ;

	/*sortArray(&arrayLikelyhood, size) ;

	*x = arrayLikelyhood[0].position[0] ;
	*y = arrayLikelyhood[0].position[1] ;
	*z = arrayLikelyhood[0].position[2] ;*/

	Likelyhood minLikelyhood = searchMin(arrayLikelyhood, size) ;

	*x = minLikelyhood.position[0] ;
	*y = minLikelyhood.position[1] ;
	*z = minLikelyhood.position[2] ;
}



