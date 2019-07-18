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
    }

    destoryMsgQueue(msgid);
    return 0;
}
