#include <stdio.h>
#include <stdlib.h>
#include "bddTdoa.h"

Tdoa createTdoaStruct(float tdoa, float x, float y, float z)
{
	Tdoa tdoaStruct ;
	tdoaStruct.tdoa = tdoa ;
	tdoaStruct.position[0] = x ;
	tdoaStruct.position[1] = y ;
	tdoaStruct.position[2] = z ;

	return tdoaStruct ;
}

void readFiles(Tdoa **arrayTdoa1, Tdoa **arrayTdoa2, Tdoa **arrayTdoa3, char * fileName1, char * fileName2, char * fileName3, int *size, int * nbX, int * nbY, int * nbZ, float * cubeSize)
{
	FILE *file1 = fopen(fileName1,"r") ;
	FILE *file2 = fopen(fileName2,"r") ;
	FILE *file3 = fopen(fileName3,"r") ;

	if(file1 != NULL && file2 != NULL && file3 != NULL)
	{
		int sizeArray, i = 0 ;
		float x, y, z, tdoa ;

		// Creation of the array dtoa1 with data from the file tdoa1-2.txt
		fscanf(file1,"%d %d %d %d %f", &sizeArray, nbX, nbY, nbZ, cubeSize) ;
		*size = sizeArray ;

		*arrayTdoa1 = malloc(sizeof(Tdoa)*sizeArray) ;

		for(i = 0 ; i<sizeArray ; i++)
		{
			fscanf(file1,"%f,%f,%f,%f",&tdoa,&x,&y,&z) ;
			Tdoa tdoaStruct = createTdoaStruct(tdoa,x,y,z) ;

			(*arrayTdoa1)[i] = tdoaStruct ;
		}

		fclose(file1) ;

		*arrayTdoa2 = malloc(sizeof(Tdoa)*sizeArray) ;

		for(i = 0 ; i<sizeArray ; i++)
		{
			fscanf(file2,"%f,%f,%f,%f",&tdoa,&x,&y,&z) ;
			Tdoa tdoaStruct = createTdoaStruct(tdoa,x,y,z) ;

			(*arrayTdoa2)[i] = tdoaStruct ;
		}

		fclose(file2) ;

		*arrayTdoa3 = malloc(sizeof(Tdoa)*sizeArray) ;

		for(i = 0 ; i<sizeArray ; i++)
		{
			fscanf(file3,"%f,%f,%f,%f",&tdoa,&x,&y,&z) ;
			Tdoa tdoaStruct = createTdoaStruct(tdoa,x,y,z) ;

			(*arrayTdoa3)[i] = tdoaStruct ;
		}

		fclose(file3) ;
 	}
}

void display(Tdoa arrayTdoa1[], Tdoa arrayTdoa2[], Tdoa arrayTdoa3[], int size)
{
	int i = 0 ;

	printf("\n\nArray 1 :\n\n") ;
	for(i = 0 ; i<size ; i++)
	{
		printf("%f %f %f %f\n", arrayTdoa1[i].tdoa, arrayTdoa1[i].position[0], arrayTdoa1[i].position[1], arrayTdoa1[i].position[2]) ;
	}

	printf("\n\nArray 2 :\n\n") ;
	for(i = 0 ; i<size ; i++)
	{
		printf("%f %f %f %f\n", arrayTdoa2[i].tdoa, arrayTdoa2[i].position[0], arrayTdoa2[i].position[1], arrayTdoa2[i].position[2]) ;
	}

	printf("\n\nArray 3 :\n\n") ;
	for(i = 0 ; i<size ; i++)
	{
		printf("%f %f %f %f\n", arrayTdoa3[i].tdoa, arrayTdoa3[i].position[0], arrayTdoa3[i].position[1], arrayTdoa3[i].position[2]) ;
	}
}
