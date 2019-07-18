#include "comm.h"

static int commMsgQueue(int flags)
{
    key_t key = ftok("/tmp", 0x6666);
    if(key < 0)
    {
        perror("ftok");
        return -1;
    }

    int msg_id = msgget(key, flags);
    if(msg_id < 0)
    {
        perror("msgget");
    }
    return msg_id;
}

int createMsgQueue()
{
    return commMsgQueue(IPC_CREAT|IPC_EXCL|0666);
}

int getMsgQueue()
{
    return commMsgQueue(IPC_CREAT);
}

int destoryMsgQueue(int msg_id)
{
    if(msgctl(msg_id, IPC_RMID, NULL) < 0)
    {
        perror("msgctl");
        return -1;
    }
    return 0;
}

int sendMsgQueue(int msg_id, int who, struct message tmpMsg)
{
    struct msgbuf buf;
    buf.mtype = who;
    //strcpy(buf.mtext, msg);
    buf.msg.index = tmpMsg.index;
    buf.msg.op = tmpMsg.op;

    if(msgsnd(msg_id, (void*)&buf, sizeof(tmpMsg), 0) < 0)
    {
        perror("msgsnd");
        return -1;
    }
    return 0;
}

int recvMsgQueue(int msg_id, int recvType, struct message *tmpMsg)
{
    struct msgbuf buf;
    //int size=sizeof(buf.mtext);
    if(msgrcv(msg_id, (void*)&buf, 8, recvType, 0) < 0)
    {
        perror("msgrcv");
        return -1;
    }
    
    tmpMsg->index = buf.msg.index;
    tmpMsg->op = buf.msg.op;

    //strncpy(out, buf.mtext, size);
    //out[size] = 0;
    return 0;
}
