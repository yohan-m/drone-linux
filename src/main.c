#include "tests/udp_async_test.h"
#include "tests/udp_disco_test.h"
#include "tests/udp_manager_test.h"
#include "tests/udp_protocol_test.h"
#include "tests/usb_test.h"
#include "tests/usb_protocol_test.h"
#include "demo/com_demo.h"
#include "usb/usb_protocol_sync.h"
#include "udp/udp_protocol.h"

#include "localization/bddTdoa.h"
#include "localization/likelyhood.h"

#include "navdata/navdataLocal.h"
#include "navdata/navdataToPC.h"
#include "navdata/navdata_manager.h"

#include "control/controlTask.h"

#include <time.h>
#include <pthread.h>

#include <unistd.h>

#define MOVING_AVG_SIZE 30

void *thread_com(void *arg) 
{	
	//init
	if(initUSBCommunicationSync()!=0) { //usb
		return;
	}
	
	if(initCommunication()!=0) { //udp
		return;
	}

	if(initNavdataCommPC()!=0){
		printf("failed to init navdata between drone and pc\n");
		return;
	}
	
	system("echo 1 > /proc/sys/net/ipv4/ip_forward");
	system("iptables -t nat -F");
	
	if(initNavdataComm()!=0){
		printf("failed to init navdata on drone\n");
		return;
	}
	
	char rule[100];
	sprintf(rule,"iptables -t nat -A POSTROUTING -p UDP --sport %d -j SNAT --to-source 127.0.0.1:%d",PORT_NAV_LOCAL,NAVDATA_PORT);
	system(rule);
	sprintf(rule,"iptables -t nat -A PREROUTING -p UDP -d 127.0.0.1 --dport %d -j DNAT --to-destination 127.0.0.1:%d",NAVDATA_PORT,PORT_NAV_LOCAL);
	system(rule);
	sprintf(rule,"iptables -t nat -A POSTROUTING -p UDP --sport %d -j SNAT --to-source 127.0.0.1:%d",CTRL_PORT_LOCAL,CTRL_PORT);
	system(rule);
	
	static pthread_mutex_t mutex_usb = PTHREAD_MUTEX_INITIALIZER;
	char type;
	float tdoa1, tdoa2, tdoa3, tdoa4 ;
	int32_t rss1, rss2, rss3, rss4;
	float tabTdoa[4] ;
	int32_t tabRss[4] ;
	float x, y, z, timeDebut, diff;

	Tdoa *arrayTdoa12 = NULL, *arrayTdoa13 = NULL, *arrayTdoa14 = NULL, *arrayTdoa21 = NULL, *arrayTdoa23 = NULL, *arrayTdoa24 = NULL;
	Tdoa *arrayTdoa31 = NULL, *arrayTdoa32 = NULL, *arrayTdoa34 = NULL, *arrayTdoa41 = NULL, *arrayTdoa42 = NULL, *arrayTdoa43 = NULL ;
	int size = 0 ;
	int nbX = 0, nbY = 0, nbZ = 0; // number of points on each axis
	int nbPtsPlan = 0; // number of points on a x-y plan
	float cubeSize = 0.0; // size of the cubes that the room are divided into
	
	float tabX[MOVING_AVG_SIZE];
	float tabY[MOVING_AVG_SIZE];
	float xAvg,yAvg;
	int indexAvg=0;
	
	int cnt;
	for (cnt = 0 ; cnt<MOVING_AVG_SIZE ; cnt++) {
		tabX[cnt]=0.0;
		tabY[cnt]=0.0;
	}

	readFiles(&arrayTdoa12,&arrayTdoa13,&arrayTdoa14,FILE_TDOA_12,FILE_TDOA_13,FILE_TDOA_14,&size,&nbX,&nbY,&nbZ, &cubeSize) ;	
	readFiles(&arrayTdoa21,&arrayTdoa23,&arrayTdoa24,FILE_TDOA_21,FILE_TDOA_23,FILE_TDOA_24,&size,&nbX,&nbY,&nbZ, &cubeSize) ;	
	readFiles(&arrayTdoa31,&arrayTdoa32,&arrayTdoa34,FILE_TDOA_31,FILE_TDOA_32,FILE_TDOA_34,&size,&nbX,&nbY,&nbZ, &cubeSize) ;	
	readFiles(&arrayTdoa41,&arrayTdoa42,&arrayTdoa43,FILE_TDOA_41,FILE_TDOA_42,FILE_TDOA_43,&size,&nbX,&nbY,&nbZ, &cubeSize) ;	
	
	nbPtsPlan = nbX*nbY;


	while(1) 
	{	
		pthread_mutex_lock(&mutex_usb);
		//read USB
		if(readUSBFrameSync(&type,&tdoa1,&tdoa2,&tdoa3,&tdoa4,&rss1,&rss2,&rss3,&rss4)==0) {
			
			tabTdoa[0] = tdoa1;
			tabTdoa[1] = tdoa2;
			tabTdoa[2] = tdoa3;
			tabTdoa[3] = tdoa4;
			tabRss[0] = rss1;
			tabRss[1] = rss2;
			tabRss[2] = rss3;
			tabRss[3] = rss4;
			//printf("tdoa1 : %f\n", (float)tdoa1*1/128) ;
			//printf("tdoa2 : %f\n", (float)tdoa2*1/128) ;
			//printf("tdoa3 : %f\n", (float)tdoa3*1/128) ;
			//printf("tdoa4 : %f\n", (float)tdoa4*1/128) ;

			timeDebut = clock() ;
			computePosition(&x, &y, &z, tabTdoa, tabRss, arrayTdoa12, arrayTdoa13, arrayTdoa14, arrayTdoa21, arrayTdoa23, arrayTdoa24, arrayTdoa31, arrayTdoa32, arrayTdoa34, arrayTdoa41, arrayTdoa42, arrayTdoa43, size, nbZ, nbPtsPlan, cubeSize, current_altitude()) ;

			diff = (float)((float)clock()-(float)timeDebut) ;///((float)CLOCKS_PER_SEC) ;
			printf("temps calcul : %f\n",diff) ;
			
			tabX[indexAvg] = x;
			tabY[indexAvg] = y;
			indexAvg = (indexAvg+1)%MOVING_AVG_SIZE;
			xAvg = 0.0;
			yAvg = 0.0;
			
			for(cnt = 0 ; cnt<MOVING_AVG_SIZE ; cnt++) {
				xAvg += tabX[cnt];
				yAvg += tabY[cnt];				
			}
			
			xAvg = xAvg/((float)MOVING_AVG_SIZE);
			yAvg = yAvg/((float)MOVING_AVG_SIZE);
			
			printf("x : %f\tx_avg : %f\n", x, xAvg) ;
			printf("y : %f\ty_avg : %f\n", y, yAvg) ;
			printf("z : %f\n", z) ;
			
			newLocalization(xAvg,yAvg);
			sendFrame(type,(int)(xAvg*100),(int)(yAvg*100),(int)(z*100),STOP_MISSION) ;
		}
		pthread_mutex_unlock(&mutex_usb);
		/*newLocalization(2.1,3.3);
		usleep(100000);*/
	}
	
	//close
	closeUSBCommunicationSync(); //usb
	closeCommunication(); //udp

	pthread_exit(NULL);
}



int main(int argc, char *argv[]) 
{
	pthread_t threadCom ;
	pthread_t threadControl ;

	printf("\nStart\n\n") ;

   	if(pthread_create(&threadCom, NULL, thread_com, NULL) == -1) {
		perror("pthread_create");
		return 1;
    	}

	if(pthread_create(&threadControl, NULL, controlTask, NULL) == -1) {
		perror("pthread_create");
		return 1;
    	}

	if (pthread_join(threadCom, NULL)) {
    		perror("pthread_join");
    		return 1;
    	}

	if (pthread_join(threadControl, NULL)) {
    		perror("pthread_join");
    		return 1;
    	}

	printf("\nEnd\n\n");

	return 0 ;	
}




