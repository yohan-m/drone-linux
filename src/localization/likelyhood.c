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

void displayArray(Likelyhood *array, int size)
{
	int i = 0 ;
	for(i = 0 ; i<size ; i++)
	{
		printf("%f %f %f %f\n", array[i].likelyhood, array[i].position[0], array[i].position[1], array[i].position[2]) ;
	}
}



