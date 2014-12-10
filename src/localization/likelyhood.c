#include "likelyhood.h"

int getNearestZ(int nbZ, float realZ, float cubeSize){
	float approxInd = realZ/cubeSize;
	if(approxInd<1.0){
		return 1;
	}
	else{
		if(fabs(approxInd-ceil(approxInd))<fabs(approxInd-floor(approxInd))){
			if((int)ceil(approxInd)<nbZ){
				return (int)ceil(approxInd);
			}
			else{
				return nbZ-1;
			}
		}
		else{
			return (int)floor(approxInd);
		}
	}
}

Likelyhood * createArrayLikelyhood(Tdoa *arrayTdoa1, Tdoa *arrayTdoa2, Tdoa *arrayTdoa3, int size, float tdoa1, float tdoa2, float tdoa3, int toIgnore, int indStart, int indFinish)
{
	Likelyhood* arrayLikelyhood = (Likelyhood*)malloc(sizeof(Likelyhood)*(indFinish-indStart+1)) ;

	int i ;
	int j =0;
	for (i = indStart ; i<indFinish ; i++)
	{
		//arrayLikelyhood[i].likelyhood = fabs(arrayTdoa1[i].tdoa - tdoa1) + fabs(arrayTdoa2[i].tdoa - tdoa2) + fabs(arrayTdoa3[i].tdoa - tdoa3) ;
		if(toIgnore==1){
			arrayLikelyhood[j].likelyhood = fabs(arrayTdoa2[i].tdoa - tdoa2) + fabs(arrayTdoa3[i].tdoa - tdoa3) ;
		}
		else if(toIgnore==2){
			arrayLikelyhood[j].likelyhood = fabs(arrayTdoa1[i].tdoa - tdoa1) + fabs(arrayTdoa3[i].tdoa - tdoa3) ;
		}
		else if(toIgnore==3){
			arrayLikelyhood[j].likelyhood = fabs(arrayTdoa2[i].tdoa - tdoa2) + fabs(arrayTdoa1[i].tdoa - tdoa1) ;
		}
		else{
			arrayLikelyhood[j].likelyhood = fabs(arrayTdoa1[i].tdoa - tdoa1) + fabs(arrayTdoa2[i].tdoa - tdoa2) + fabs(arrayTdoa3[i].tdoa - tdoa3) ;
		}
		arrayLikelyhood[j].position[0] = arrayTdoa1[i].position[0] ;
		arrayLikelyhood[j].position[1] = arrayTdoa1[i].position[1] ;
		arrayLikelyhood[j].position[2] = arrayTdoa1[i].position[2] ;
		j++;
	}

	return arrayLikelyhood ;
}


int sortArray(Likelyhood **array, int size, int nbZ, int nbPtsPlan, float cubeSize, float realZ)
{
	int i ;
	Likelyhood temp ;
	int sorted = 0 ;
	int indStart = 0, indFinish = 0;
	int indZMoy = getNearestZ(nbZ, realZ,cubeSize);
	indStart = (indZMoy-1)*nbPtsPlan;
	indFinish = (indZMoy+1)*nbPtsPlan-1;
	
	while (!sorted)
	{
		sorted = 1 ;

		for(i = indStart ; i<indFinish ; i++)
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
	
	return indStart;
}

Likelyhood searchMin(Likelyhood *array, int size, int nbZ, int nbPtsPlan, float cubeSize, float realZ)
{
	int i = 0, indMin = 0 ;
	float min = 1000.0 ;
	Likelyhood likelyhood ;
	int indStart = 0, indFinish = 0;
	int indZMoy = getNearestZ(nbZ, realZ,cubeSize);
	indStart = (indZMoy-1)*nbPtsPlan;
	indFinish = (indZMoy+1)*nbPtsPlan-1;

	for(i = 0 ; i<3*nbPtsPlan-1 ; i++)
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

void computePosition(float *x, float *y, float *z, int32_t * tabTdoa, int32_t * tabRss, Tdoa *arrayTdoa12, Tdoa *arrayTdoa13, Tdoa *arrayTdoa14, Tdoa *arrayTdoa21, Tdoa *arrayTdoa23, Tdoa *arrayTdoa24, Tdoa *arrayTdoa31, Tdoa *arrayTdoa32, Tdoa *arrayTdoa34, Tdoa *arrayTdoa41, Tdoa *arrayTdoa42, Tdoa *arrayTdoa43, int size, int nbZ, int nbPtsPlan, float cubeSize, float realZ)
{
	//float tdoa12 = 0.0, tdoa13 = 0.0, tdoa14 = 0.0 ;
	Likelyhood *arrayLikelyhood = NULL ;

	/*tdoa12 = (float)(tdoa2 - tdoa1) * 1.0/128.0;
	tdoa13 = (float)(tdoa3 - tdoa1) * 1.0/128.0;
	tdoa14 = (float)(tdoa4 - tdoa1) * 1.0/128.0;*/
	
	// calculating necessary work interval
	int indStart = 0, indFinish = 0;
	int indZMoy = getNearestZ(nbZ, realZ,cubeSize);
	indStart = (indZMoy-1)*nbPtsPlan;
	indFinish = indStart+3*nbPtsPlan-1;//(indZMoy+1)*nbPtsPlan-1;
	// searching for min rss
	int indMinRss = -1, minRss = 100000000, indMaxRss = -1, maxRss = -1, i;
	for(i=0;i<4;i++){
		if(tabRss[i]<minRss){
			indMinRss = i;
			minRss = tabRss[i];
		}
		if(tabRss[i]>maxRss){
			indMaxRss = i;
			maxRss = tabRss[i];
		}
	}
	printf("indmin=%d\tindmax=%d\n",indMinRss+1,indMaxRss+1);
	for(i=0;i<4;i++){
		printf("tdoa[%d]=%d\n",i+1,tabTdoa[i]);
	}
	
	/*if(tdoa2!=0)
		tdoa12 = (float)(tdoa2 - tdoa1) * 1.0/2.0;
	else
		tdoa12 = 0.0;
	if(tdoa3!=0)
		tdoa13 = (float)(tdoa3 - tdoa1) * 1.0/2.0;
	else
		tdoa12 = 0.0;
	if(tdoa4!=0)
		tdoa14 = (float)(tdoa4 - tdoa1) * 1.0/2.0;
	else
		tdoa12 = 0.0;*/

	//displayArray(arrayTdoa1, size) ;

	// creating likelihood array according to which reference was chosen (ref = rss max)
	switch(indMaxRss){
		case 0:
			arrayLikelyhood = createArrayLikelyhood(arrayTdoa12, arrayTdoa13, arrayTdoa14, size, (float)tabTdoa[1], (float)tabTdoa[2], (float)tabTdoa[3],indMinRss,indStart,indFinish) ;
			break;
		case 1:
			if(indMinRss==0)
				indMinRss=1;
			arrayLikelyhood = createArrayLikelyhood(arrayTdoa21, arrayTdoa23, arrayTdoa24, size, (float)tabTdoa[0], (float)tabTdoa[2], (float)tabTdoa[3],indMinRss,indStart,indFinish) ;
			break;
		case 2:
			if(indMinRss==0)
				indMinRss=1;
			else if(indMinRss==1)
				indMinRss=2;
			arrayLikelyhood = createArrayLikelyhood(arrayTdoa31, arrayTdoa32, arrayTdoa34, size, (float)tabTdoa[0], (float)tabTdoa[1], (float)tabTdoa[3],indMinRss,indStart,indFinish) ;
			break;
		case 3:
			arrayLikelyhood = createArrayLikelyhood(arrayTdoa41, arrayTdoa42, arrayTdoa43, size, (float)tabTdoa[0], (float)tabTdoa[1], (float)tabTdoa[2],indMinRss+1,indStart,indFinish) ;
			break;
		default:
			break;
	}
	//arrayLikelyhood = createArrayLikelyhood(arrayTdoa12, arrayTdoa13, arrayTdoa14, size, tdoa12, tdoa13, tdoa14) ;

	/*int indMin = sortArray(&arrayLikelyhood, size, nbZ, nbPtsPlan, cubeSize, realZ) ;

	*x = arrayLikelyhood[indMin].position[0] ;
	*y = arrayLikelyhood[indMin].position[1] ;
	*z = realZ;//arrayLikelyhood[indMin].position[2] ;*/

	Likelyhood minLikelyhood = searchMin(arrayLikelyhood, size, nbZ, nbPtsPlan, cubeSize, realZ) ;
	free(arrayLikelyhood);
	*x = minLikelyhood.position[0] ;
	*y = minLikelyhood.position[1] ;
	*z = realZ;//minLikelyhood.position[2] ;
}



