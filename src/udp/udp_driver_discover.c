#include "udp_driver_discover.h"


int udp_driver_discover_network(int local_port, int remote_port, unsigned char * discovery_frame, int discovery_size, unsigned char * response_frame, int response_size, int delay_ms, char * IP)
{
	//init
	
	//create the socket
	if ((disco_socket_fd=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP))==-1) {
		printf("[Error] L%d %s : %s\n",__LINE__,__FUNCTION__,strerror(errno));
		return -1;
	}	
		
	int socket_flag = 1;
	if (setsockopt (disco_socket_fd, SOL_SOCKET, SO_BROADCAST,&socket_flag,sizeof(socket_flag))<0) {
		printf("[Error] L%d %s : %s\n",__LINE__,__FUNCTION__,strerror(errno));
		return -2;
	}

	//configure the sockaddr structure for the reception
	memset((char *) &disco_local_sockaddr, 0, sizeof(disco_local_sockaddr));
	disco_local_sockaddr.sin_family = AF_INET;
	disco_local_sockaddr.sin_port = htons(local_port);
	disco_local_sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);

	//bind the sockaddr structure to the socket
	if (bind(disco_socket_fd, (struct sockaddr*)&disco_local_sockaddr, sizeof(disco_local_sockaddr))==-1) {
		printf("[Error] L%d %s : %s\n",__LINE__,__FUNCTION__,strerror(errno));
		return -3;
	}

	//configure the sockaddr structure for the emission
	memset((char *) &disco_remote_sockaddr, 0, sizeof(disco_remote_sockaddr));
	disco_remote_sockaddr.sin_family = AF_INET;
	disco_remote_sockaddr.sin_port = htons(remote_port);
	if (inet_aton("192.168.1.255", &disco_remote_sockaddr.sin_addr)==0) {
		printf("[Error] L%d %s : inet_aton failed\n",__LINE__,__FUNCTION__);
		return -4;
	}

	//enable async read
	
	int flags;
	struct sigaction sa;
	
	//get global variable for the handler
	disco_response_size = response_size;
	disco_response_frame = response_frame;
	disco_found = 0;

	//add ASYNC flags to the socket
	flags = fcntl(disco_socket_fd, F_GETFL);
	if(fcntl(disco_socket_fd, F_SETFL, flags | O_ASYNC)<0) {
		printf("[Error] L%d %s : %s\n",__LINE__,__FUNCTION__,strerror(errno));
		return -5;
	}
		
	//configure the sigaction structure
	sa.sa_flags = 0;
	sa.sa_handler = udp_driver_discover_handler;
	sigemptyset(&sa.sa_mask);

	//get the signal
	if (sigaction(SIGIO, &sa, NULL)<0) {
		printf("[Error] L%d %s : %s\n",__LINE__,__FUNCTION__,strerror(errno));
		return -6;	
	}

	//indicate this pid will receive the signal
	if (fcntl(disco_socket_fd, F_SETOWN, getpid())<0) {
		printf("[Error] L%d %s : %s\n",__LINE__,__FUNCTION__,strerror(errno));
		return -7;	
	}

	//set the signal sent
	if (fcntl(disco_socket_fd, F_SETSIG, SIGIO)<0) {
		printf("[Error] L%d %s : %s\n",__LINE__,__FUNCTION__,strerror(errno));
		return -8;	
	}
	
	
	//send the discovery frame
	
	#ifdef DEBUG
		printf("Discovering ...\n");
	#endif
	
	int slen = sizeof(disco_remote_sockaddr);	
	int cnt_bytes = sendto(disco_socket_fd, discovery_frame, discovery_size, 0, (struct sockaddr *)&disco_remote_sockaddr, (socklen_t)slen);	
	if (cnt_bytes==-1) {
		printf("[Error] L%d %s : %s\n",__LINE__,__FUNCTION__,strerror(errno));
		if(close(disco_socket_fd)<0) {
			printf("[Error] L%d %s : %s\n",__LINE__,__FUNCTION__,strerror(errno));
			return -9;
		}
		return -10;
	}
	
	#ifdef DEBUG
		printf("[Debug] L%d %s : write %d bytes to %s:%d : ",__LINE__,__FUNCTION__,cnt_bytes,inet_ntoa(disco_remote_sockaddr.sin_addr),ntohs(disco_remote_sockaddr.sin_port));
		int i;
		for(i=0 ; i<cnt_bytes ; i++) {
			printf("0x%X ",discovery_frame[i]);
		}	
		printf("\n");
	#endif
	
	//wait for a response
	int time = 0;
	while(time<delay_ms) {
		usleep(10000);	
		time+=10;
	}
	
	if(close(disco_socket_fd)<0) {
		printf("[Error] L%d %s : %s\n",__LINE__,__FUNCTION__,strerror(errno));
		return -11;
	}
	
	if(disco_found>0) {
		memcpy(IP,disco_ip,IP_SIZE);
		#ifdef DEBUG
			printf("[Debug] L%d %s : Discovering finished %s\n",__LINE__,__FUNCTION__,IP);
		#endif		
	}
	else {
		IP[0] = '\0';
		#ifdef DEBUG
			printf("[Debug] L%d %s : Discovering finished, computer not found\n",__LINE__,__FUNCTION__);
		#endif
	}	
	
	return 0;
}


void udp_driver_discover_handler(int sig) 
{
	unsigned char data[disco_response_size];
	struct sockaddr_in disco_sender_sockaddr;
	int slen=sizeof(disco_sender_sockaddr);
	
	int cnt_bytes = recvfrom(disco_socket_fd, data, disco_response_size, 0, (struct sockaddr *)&disco_sender_sockaddr, (socklen_t *)&slen);

	if (cnt_bytes<0) {
		printf("[Error] L%d %s : %s\n",__LINE__,__FUNCTION__,strerror(errno));
		return;	
	}
	
	if(cnt_bytes == disco_response_size && memcmp(data,disco_response_frame,disco_response_size)==0) {
		disco_found++;
		disco_ip = (char *)inet_ntoa(disco_sender_sockaddr.sin_addr);
		
		#ifdef DEBUG
			printf("[Debug] L%d %s : Response from %s\n",__LINE__,__FUNCTION__,disco_ip);
		#endif	
	}
	else {
		#ifdef DEBUG
			printf("[Debug] L%d %s : Unknown response : %d bytes from %s:%d : ",__LINE__,__FUNCTION__,cnt_bytes,inet_ntoa(disco_sender_sockaddr.sin_addr),ntohs(disco_sender_sockaddr.sin_port));	
			int i;
			for(i=0 ; i<cnt_bytes ; i++) {
				printf("0x%X ",data[i]);
			}
			printf("(%s)\n",data);
		#endif
	}
	
	
	

}
