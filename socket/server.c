#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

#define ERR_EXIT(m) \
	do \
	{ \
		perror(m); \
		exit(EXIT_FAILURE); \
	} while(0)

int main(void)
{
	int listenfd;
	if ((listenfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
	{
		ERR_EXIT("socket");
	}
	struct sockaddr_in servaddr;
	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(5188);
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	if((bind(listenfd, (struct sockaddr*) &servaddr, sizeof(servaddr))) < 0) 
	{
		ERR_EXIT("bind");
	}
	if (listen(listenfd, 10) < 0)
	{
		ERR_EXIT("listen");
	} 
	
	struct sockaddr_in peeraddr;
	socklen_t peerlen = sizeof(peeraddr);
	int conn;	
	if ((conn = accept(listenfd, (struct sockaddr*) &peeraddr, &peerlen)) < 0)
	{
		ERR_EXIT("accept");
	}
	
	char recvbuf[1024]={0};
	while(1)
	{
		memset(recvbuf, 0, sizeof(recvbuf));
		int ret = read(conn, recvbuf, sizeof(recvbuf));
		//fputs(ret, stdout);
		fputs(recvbuf, stdout);
		write(conn, recvbuf, ret);
	}

	close(conn);
	close(listen);
	return 0;



}
