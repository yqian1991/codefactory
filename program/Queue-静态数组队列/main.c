#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 10

//静态数组队列,队列的删除和增加体现在front和rear的变化
typedef struct
{
    char *base;//初始化的动态分配存储空间
    int front;
    int rear;

}squeue;

void initQueue(squeue *q)
{
    q->base=malloc(MAX_SIZE*sizeof(char));
    if(!q->base)//存储分配失败
        exit(0);
        q->front=q->rear=0;//队列空

}

void destroyQueue(squeue *q)//销毁队列
{
    if(q->base)
        free(q->base);
    q->base = NULL;
    q->front=q->rear = 0;
}

void clearQueue(squeue *q)//清空队列
{
    q->front=q->rear = 0;
}

int queueLength(squeue *q)//队列长度
{
    return ((q->rear)-(q->front)+MAX_SIZE)%MAX_SIZE;
}

void enQueue(squeue *q, char item)
{
    q->rear=(++(q->rear))%MAX_SIZE;

    if(q->rear == q->front)
    {
        printf("queue is null\n");
        if(!q->front)
            q->rear=MAX_SIZE-1;
        else
            q->rear--;
    }else{
        //printf("before insert:%d\n",q->rear);
        q->base[q->rear] = item;
        printf("item enter:%c. \n",item);
        //printf("after insert:%d\n",q->rear);
    }
}

void deleteQueue(squeue *q)
{
    if(q->rear == q->front)
    {
        printf("queue is empty\n");
    }else{
        printf("delete:%c.\n",q->front);
        q->front = ((q->front)+1)%MAX_SIZE;
    }
}
void queueTraverse(squeue*q)
{
    int i=0;
    for(i=q->front;i<=q->rear;i++)
    {
        printf("%c",q->base[i]);
    }
}
int main()
{
    squeue* q;
    initQueue(q);
    enQueue(q,'q');
    enQueue(q,'i');
    enQueue(q,'a');
    enQueue(q,'n');
    printf("%d.\n",queueLength(q));
    deleteQueue(q);
    printf("%d.\n",queueLength(q));
    queueTraverse(q);
    return 0;
}
