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

#include <time.h>
#include <pthread.h>

#define PERIODE_THREAD_CONTROL 30

void *thread_control(void *arg)
{
	struct timespec time ;
	int i = 0 ;

	pthread_mutex_t verrou; 
	pthread_cond_t cond; 

	pthread_cond_init(&cond, NULL); 
        pthread_mutex_init(&verrou, NULL); 

	clock_gettime(CLOCK_REALTIME, &time); 
	while(i <10 )
	{
		pthread_mutex_lock(&verrou); 
   		time.tv_sec = time.tv_sec + PERIODE_THREAD_CONTROL; 
    		printf("Activation periodique de la tâche thread_control %d secondes\n", (int) time.tv_sec); 
    		//suite du code 
    		pthread_cond_timedwait(&cond, &verrou, &time); 
    		pthread_mutex_unlock(&verrou); 
    		i++; 
		
	}
	pthread_exit(NULL) ; 
}

void *thread_com(void *arg) 
{	
	//init
	if(initUSBCommunicationSync()!=0) { //usb
		return;
	}
	
	if(initCommunication()!=0) { //udp
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
	sprintf(rule,"iptables -t nat -A PREROUTING -p UDP -d %s -j DNAT --to-destination %s:%d",IP,IP,REMOTE_PORT);
	system(rule);
	
	if(initNavdataCommPC()!=0){
		printf("failed to init navdata between drone and pc\n");
		return;
	}
	

	char type;
	uint32_t tdoa1, tdoa2, tdoa3, tdoa4 ;
	float x, y, z, timeDebut, diff ;

	Tdoa *arrayTdoa1 = NULL, *arrayTdoa2 = NULL, *arrayTdoa3 = NULL ;
	int size = 0 ;

	readFiles(&arrayTdoa1,&arrayTdoa2,&arrayTdoa3,&size) ;	
	
	while(1) 
	{	
		//read USB
		if(readUSBFrameSync(&type,&tdoa1,&tdoa2,&tdoa3,&tdoa4)==0) {
		
		//printf("tdoa1 : %f\n", (float)tdoa1*1/128) ;
		//printf("tdoa2 : %f\n", (float)tdoa2*1/128) ;
		//printf("tdoa3 : %f\n", (float)tdoa3*1/128) ;
		//printf("tdoa4 : %f\n", (float)tdoa4*1/128) ;

		timeDebut = clock() ;
		computePosition(&x, &y, &z, tdoa1, tdoa2, tdoa3, tdoa4, arrayTdoa1, arrayTdoa2, arrayTdoa3,size) ;

		diff = (float)((float)clock()-(float)timeDebut) ;///((float)CLOCKS_PER_SEC) ;
		printf("temps calcul : %f\n",diff) ;

		//printf("x : %f\n", x) ;
		//printf("y : %f\n", y) ;
		//printf("z : %f\n", z) ;

		sendFrame(type,(int)x*100,(int)y*100,(int)z*100,STOP_MISSION) ;
		}
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

	if(pthread_create(&threadControl, NULL, thread_control, NULL) == -1) {
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




