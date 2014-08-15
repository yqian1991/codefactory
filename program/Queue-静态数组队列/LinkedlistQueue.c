#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 10

//链队列,
typedef struct QNode
{
    char *data;
    struct QNode* next;
}QNode,*queue;

typedef struct
{
    queue front, rear;
}LinkQueue;

void initQueue(LinkQueue *q)
{
    q->front=q->rear=malloc(sizeof(QNode));
    if(!q->front)//存储分配失败
        exit(0);
        q->front->next=NULL;//队列空

}

void destroyQueue(LinkQueue *q)//销毁队列
{
    while(q->front)
    {
        q->rear=q->front->next;
        free(q->front);
        q->front=q->rear;
    }
}

void clearQueue(LinkQueue *q)//清空队列
{
    queue p,t;
    q->rear=q->front;
    p=q->front->next;
    q->front->next=NULL;//队列已经空
    while(p)//将元素删除，释放存储空间
    {
        t=p;
        p=p->next;
        free(t);
    }
}

int queueLength(LinkQueue *q)//队列长度
{
    int i=0;
    queue p;
    p=q->front;
    while(p)
    {
        i++;
        p=p->next;
    }
    return i;
}

void enQueue(LinkQueue *q, char item)
{
    queue p=malloc(sizeof(QNode));
    p->data=item;
    p->next = NULL;
    q->rear->next=p;//
    q->rear=p;//p是新的队尾
}

void deleteQueue(LinkQueue *q)
{
    if(q->front==q->rear)
        printf("queue empty");

    queue p = q->front->next;
    q->front->next=p->next;

    if(q->rear==p)
        q->rear=q->front;

    free(p);
}
void queueTraverse(LinkQueue*q)
{
    queue p;
    p=q->front->next;
    while(p)
    {
        printf("%c,",p->data);
        p=p->next;
    }
    printf(".\n");
}
int main()
{
    LinkQueue* q;
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
