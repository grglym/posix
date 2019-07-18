#include "comm.h"

int main()
{
    int msgid = getMsgQueue();

    //char buf[1024] = {0};
    struct msgbuf buf;
    while(1)
    {
        printf("Please Enter# ");
        fflush(stdout);
	scanf("%d %d",&buf.msg.index, &buf.msg.op);
        sendMsgQueue(msgid, CLIENT_TYPE, buf.msg);
        printf("send done, wait recv...\n");
        recvMsgQueue(msgid, SERVER_TYPE, &buf.msg);
        printf("server# %d %d\n", buf.msg.index, buf.msg.op);
    }
    return 0;
}
