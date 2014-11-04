#include "udp_async_driver.h"

int udp_async_driver_init(int local_port, int remote_port, char * remote_addr)
{
	//create the socket
	if ((async_socket_fd=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP))==-1) {
		printf("[Error] L%d %s : %s\n",__LINE__,__FUNCTION__,strerror(errno));
		return -1;
	}

	//configure the sockaddr structure for the reception
	memset((char *) &async_local_sockaddr, 0, sizeof(async_local_sockaddr));
	async_local_sockaddr.sin_family = AF_INET;
	async_local_sockaddr.sin_port = htons(local_port);
	async_local_sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);

	//bind the sockaddr structure to the socket
	if (bind(async_socket_fd, (struct sockaddr*)&async_local_sockaddr, sizeof(async_local_sockaddr))==-1) {
		printf("[Error] L%d %s : %s\n",__LINE__,__FUNCTION__,strerror(errno));
		return -2;
	}

	//configure the sockaddr structure for the emission
	memset((char *) &async_remote_sockaddr, 0, sizeof(async_remote_sockaddr));
	async_remote_sockaddr.sin_family = AF_INET;
	async_remote_sockaddr.sin_port = htons(remote_port);
	if (inet_aton(remote_addr, &async_remote_sockaddr.sin_addr)==0) {
		printf("[Error] L%d %s : inet_aton failed\n",__LINE__,__FUNCTION__);
		return -3;
	}
	
	#ifdef DEBUG
		printf("[Debug] L%d %s : Ok\n",__LINE__,__FUNCTION__);		
	#endif

	return 0;
}


int udp_async_driver_close()
{
	if(close(async_socket_fd)<0) {
		printf("[Error] L%d %s : %s\n",__LINE__,__FUNCTION__,strerror(errno));
		return -1;
	}
	
	#ifdef DEBUG
		printf("[Debug] L%d %s : Ok\n",__LINE__,__FUNCTION__);		
	#endif
	
	return 0;
}


int udp_async_driver_enable_read(udp_function callback_receive_fct, int max_packet_size)
{
	int flags;
	struct sigaction sa;
	
	//get global variable for the handler
	async_packet_size = max_packet_size;
	callback_receive_udp = callback_receive_fct;

	//add ASYNC flags to the socket
	flags = fcntl(async_socket_fd, F_GETFL);
	if(fcntl(async_socket_fd, F_SETFL, flags | O_ASYNC)<0) {
		printf("[Error] L%d %s : %s\n",__LINE__,__FUNCTION__,strerror(errno));
		return -1;
	}
		
	//configure the sigaction structure
	sa.sa_flags = 0;
	sa.sa_handler = udp_async_driver_handler;
	sigemptyset(&sa.sa_mask);

	//get the signal
	if (sigaction(SIGIO, &sa, NULL)<0) {
		printf("[Error] L%d %s : %s\n",__LINE__,__FUNCTION__,strerror(errno));
		return -2;	
	}

	//indicate this pid will receive the signal
	if (fcntl(async_socket_fd, F_SETOWN, getpid())<0) {
		printf("[Error] L%d %s : %s\n",__LINE__,__FUNCTION__,strerror(errno));
		return -3;	
	}

	//set the signal sent
	if (fcntl(async_socket_fd, F_SETSIG, SIGIO)<0) {
		printf("[Error] L%d %s : %s\n",__LINE__,__FUNCTION__,strerror(errno));
		return -4;	
	}
    
	#ifdef DEBUG
		printf("[Debug] L%d %s : Ok\n",__LINE__,__FUNCTION__);		
	#endif
    
	return 0;
}


int udp_async_driver_write(unsigned char * data, int size)
{
	int slen = sizeof(async_remote_sockaddr);
	
	int cnt_bytes = sendto(async_socket_fd, data, size, 0, (struct sockaddr *)&async_remote_sockaddr, (socklen_t)slen);
	
	if (cnt_bytes==-1) {
		printf("[Error] L%d %s : %s\n",__LINE__,__FUNCTION__,strerror(errno));
		return -1;
	}

	#ifdef DEBUG
		printf("[Debug] L%d %s : %d bytes to %s:%d : ",__LINE__,__FUNCTION__,cnt_bytes,inet_ntoa(async_remote_sockaddr.sin_addr),ntohs(async_remote_sockaddr.sin_port));	
		int i;
		for(i=0 ; i<cnt_bytes ; i++) {
			printf("0x%X ",data[i]);
		}
		printf("(%s)\n",data);
	#endif
	
	return cnt_bytes;
}


void udp_async_driver_handler(int sig) 
{
	unsigned char data[async_packet_size];
	struct sockaddr_in async_sender_sockaddr;
	int slen=sizeof(async_sender_sockaddr);
	
	int cnt_bytes = recvfrom(async_socket_fd, data, async_packet_size, 0, (struct sockaddr *)&async_sender_sockaddr, (socklen_t *)&slen);

	if (cnt_bytes<0) {
		printf("[Error] L%d %s : %s\n",__LINE__,__FUNCTION__,strerror(errno));
		return;	
	}
	
	#ifdef DEBUG
		printf("[Debug] L%d %s : %d bytes from %s:%d : ",__LINE__,__FUNCTION__,cnt_bytes,inet_ntoa(async_sender_sockaddr.sin_addr),ntohs(async_sender_sockaddr.sin_port));	
		int i;
		for(i=0 ; i<cnt_bytes ; i++) {
			printf("0x%X ",data[i]);
		}
		printf("(%s)\n",data);
	#endif
	
	callback_receive_udp(data,cnt_bytes);
}





