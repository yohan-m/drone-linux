#include "udp_driver.h"


int udp_driver_init(int local_port, int remote_port, char * remote_addr)
{
	//create the socket
	if ((socket_fd=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP))==-1) {
		printf("[Error] L%d %s : %s\n",__LINE__,__FUNCTION__,strerror(errno));
		return -1;
	}

	//configure the sockaddr structure for the reception
	memset((char *) &local_sockaddr, 0, sizeof(local_sockaddr));
	local_sockaddr.sin_family = AF_INET;
	local_sockaddr.sin_port = htons(local_port);
	local_sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);

	//bind the sockaddr structure to the socket
	if (bind(socket_fd, (struct sockaddr*)&local_sockaddr, sizeof(local_sockaddr))==-1) {
		printf("[Error] L%d %s : %s\n",__LINE__,__FUNCTION__,strerror(errno));
		return -2;
	}

	//configure the sockaddr structure for the emission
	memset((char *) &remote_sockaddr, 0, sizeof(remote_sockaddr));
	remote_sockaddr.sin_family = AF_INET;
	remote_sockaddr.sin_port = htons(remote_port);
	if (inet_aton(remote_addr, &remote_sockaddr.sin_addr)==0) {
		printf("[Error] L%d %s : inet_aton failed\n",__LINE__,__FUNCTION__);
		return -3;
	}
	
	#ifdef DEBUG
		printf("[Debug] L%d %s : Ok\n",__LINE__,__FUNCTION__);		
	#endif

	return 0;
}


int udp_driver_close()
{
	if(close(socket_fd)<0) {
		printf("[Error] L%d %s : %s\n",__LINE__,__FUNCTION__,strerror(errno));
		return -1;
	}
	
	#ifdef DEBUG
		printf("[Debug] L%d %s : Ok\n",__LINE__,__FUNCTION__);		
	#endif
	
	return 0;
}


int udp_driver_write(unsigned char * data, int size)
{
	int slen = sizeof(remote_sockaddr);
	
	int cnt_bytes = sendto(socket_fd, data, size, 0, (struct sockaddr *)&remote_sockaddr, (socklen_t)slen);
	
	if (cnt_bytes<0) {
		printf("[Error] L%d %s : %s\n",__LINE__,__FUNCTION__,strerror(errno));
		return -1;
	}

	#ifdef DEBUG
		printf("[Debug] L%d %s : %d bytes to %s:%d : ",__LINE__,__FUNCTION__,cnt_bytes,inet_ntoa(remote_sockaddr.sin_addr),ntohs(remote_sockaddr.sin_port));
		int i;
		for(i=0 ; i<cnt_bytes ; i++) {
			printf("0x%X ",data[i]);
		}
		printf("(%s)\n",data);	
	#endif
	return 0;
}


int udp_driver_read(unsigned char * data, int size)
{
	struct sockaddr_in sender_sockaddr;
	
	int slen = sizeof(sender_sockaddr);
	
	int cnt_bytes = recvfrom(socket_fd, data, size, 0, (struct sockaddr *)&sender_sockaddr, (socklen_t *)&slen);

	if(cnt_bytes<0) {
		printf("[Error] L%d %s : %s\n",__LINE__,__FUNCTION__,strerror(errno));
		return -1;
	}

	#ifdef DEBUG
		printf("[Debug] L%d %s : %d bytes from %s:%d : ",__LINE__,__FUNCTION__,cnt_bytes,inet_ntoa(sender_sockaddr.sin_addr),ntohs(sender_sockaddr.sin_port));	
		int i;
		for(i=0 ; i<cnt_bytes ; i++) {
			printf("0x%X ",data[i]);
		}
		printf("(%s)\n",data);
	#endif
	return 0;
}



