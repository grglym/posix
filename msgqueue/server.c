#include "comm.h"

int main()
{
    int msgid = createMsgQueue();

    //char buf[1024] = {0};
    struct message msg;
    while(1)
    {
        recvMsgQueue(msgid, CLIENT_TYPE, &msg);

        printf("Please enter# ");
	printf("%d %d",msg.index, msg.op);
        fflush(stdout);
	scanf("%d %d",&msg.index, &msg.op);
        sendMsgQueue(msgid, SERVER_TYPE, msg);
        printf("send done, wait recv...\n");
    
	int status,i;
	for(i=0; i<4; i++)
	{
		status=fork();
		if(status == 0 || status == -1)break;
	}
	if(status == -1)
		exit(EXIT_FAILURE);
	else if(status == 0)
	{
		recvMsgQueue(msgid, CLIENT_TYPE, &msg);
		printf("%d %d",msg.index, msg.op);
		exit(0);
	}
    }

    destoryMsgQueue(msgid);
    return 0;
}
