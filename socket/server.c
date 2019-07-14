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

void do_service(int conn)
{
	char recvbuf[1024]={0};
        while(1)
        {
                memset(recvbuf, 0, sizeof(recvbuf));
        	
		
		int ret = read(conn, recvbuf, sizeof(recvbuf));
		if(ret == 0)
		{
			printf("client close\n");
			break;
		}
		fputs(recvbuf, stdout);
                write(conn, recvbuf, ret);	
	}
}
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

	int on = 1;
	if(setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) < 0)
	{
		ERR_EXIT("setsockopt");
	}


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
	
	while(1)
	{
		if ((conn = accept(listenfd, (struct sockaddr*) &peeraddr, &peerlen)) < 0)
		{
			ERR_EXIT("accept");
		}
	
		printf("ip=%s port=%d\n", inet_ntoa(peeraddr.sin_addr), ntohs(peeraddr.sin_port));
		
		int pid = fork();
		if(pid == -1)
		{
			ERR_EXIT("fork");
		}
		if(pid == 0)
		{
			close(listenfd);
			do_service(conn);
			exit(EXIT_SUCCESS);
		}
		else {
			close(conn);
		}
	} 
	return 0;
}
