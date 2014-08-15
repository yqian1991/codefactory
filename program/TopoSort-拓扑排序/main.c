#include "stdio.h"
#include "conio.h"
#include "stdlib.h"

#define MAX_VERTEX_NUM 20//��󶥵���
#define STACK_INIT_SIZE 16//ջ��С
#define STACKINCREMENT 5

typedef  int SElemType;
typedef char VertexType;

typedef struct
{
    SElemType *base;
    SElemType *top;
    int stacksize;
}SqStack;

//���ڽӱ�����ͼ�Ĵ洢�ṹ
typedef struct ArcNode
{
       int adjvex;
       struct ArcNode *nextarc;
       int info;
}ArcNode;  //�߱�������

//��������
typedef struct VNode
{
       VertexType data;
       int count;
       ArcNode *firstarc;
}VNode,AdjList[MAX_VERTEX_NUM]; //ͷ���

typedef struct
{
       AdjList vertices;  //�ڽӱ�
       int vexnum,arcnum;
}ALGraph;

int InitStack(SqStack *S)
{
    printf("��ʼ����ջ��\n");
    S->base=(SElemType*)malloc(STACK_INIT_SIZE*sizeof(SElemType));
    if(!S->base)
        exit(-1);
    S->top=S->base;
    S->stacksize=STACK_INIT_SIZE;
    return 1;
}//InitStack

int Push(SqStack *S,SElemType e)
{
    if((S->top-S->base)>=S->stacksize)
    {
        S->base=(SElemType*)realloc(S->base,(S->stacksize+STACKINCREMENT)*sizeof(SElemType));
        if(!S->base)
            exit(-1);
        S->top=S->base+S->stacksize;
        S->stacksize+=STACKINCREMENT;
    }//if
    *(S->top)=e;
    S->top++;
    return 1;

}//Push

int Pop(SqStack *S,SElemType *e)
{
    if(S->top==S->base)
        return 0;
    --(S->top);
    e=*(S->top);
    return 1;
}//Pop

int StackEmpty(SqStack *S)
{
    if(S->top==S->base)
        return 1;
    else
        return 0;
}//StackEmpty

int LocateVex(ALGraph *G,char u)
{
    int i;
    for (i=0;i<G->vexnum;i++)
    {
        if(u==G->vertices[i].data)
            return i;
    }
    if (i==G->vexnum)
    {
        printf("Error u!\n");
        exit(1);
    }
    return 0;
}

void CreateALGraph_adjlist(ALGraph *G)
{
    int i,j,k,w;
    char v1,v2,enter;
    ArcNode *p;
    printf("Input vexnum & arcnum:\n");
    scanf("%d",&(G->vexnum));
    scanf("%d",&(G->arcnum));

    printf("Input Vertices(�Իس�������������),��%d������:\n",G->vexnum);
    for (i=0;i<G->vexnum;i++)
    {
        scanf("%c%c",&enter,&(G->vertices[i].data));//���붥��
        G->vertices[i].firstarc=NULL;
    }//for

    printf("Input Arcs(v1,v2,w)�Իس��ֿ��������ݣ���%d����:\n",G->arcnum);
    for (k=0;k<G->arcnum;k++)
    {
        scanf("%c%c",&enter,&v1);
        scanf("%c%c",&enter,&v2);
              //scanf("%d",&w);
        i=LocateVex(G,v1);
        j=LocateVex(G,v2);
        p=(ArcNode*)malloc(sizeof(ArcNode));
        p->adjvex=j;
        //p->info = w;
        p->nextarc=G->vertices[i].firstarc; //ǰ�巨,��ÿ�ζ����뵽ͷ���ĺ���
        G->vertices[i].firstarc=p;
        printf("Next\n");
    }//for
    printf("ͼ�������\n");
}//CreateALGraph_adjlist

//Ѱ�����
void FindInDegree(ALGraph *G)
{
    printf("***Ϊ%d�����㽨��������ݣ�\n",G->vexnum);
    int i,j;
    for(i=0;i<G->vexnum;i++)
    {
        G->vertices[i].count=0;//��count����ȣ���ʼ��Ϊ0
    }//end for
    printf("******��ȳ�ʼ��Ϊ0���\n");
    for(j=0;j<G->vexnum;j++)
    {
       //calculate indgrees for every Arc node
       /*all the arc in current node should add 1 to its arc's count,
        because current node marks a indegree for all arcs*/
       ArcNode *p=NULL;
       for(p=G->vertices[j].firstarc;p;p=p->nextarc)
         G->vertices[p->adjvex].count++;
    }//end for
    printf("******��ȼ������\n");
}//end FindInDegree

//��������������
int TopoSort(ALGraph *G)
{
    printf("������������\n");
    SqStack *S;
    FindInDegree(G);//
    InitStack(S);

    int i=0;
    for(i=0;i<G->vexnum;i++)
       if(G->vertices[i].count==0)//everytime, we find the node whose count is 0, means that indegree is 0
        Push(S,i);//push to stack S

    int countt=0;
    while(!StackEmpty(S))
    {
       int i,m;
       m=Pop(S,i);//pop this node ,add to topo ;list;
       printf(" %c",G->vertices[i].data);
       ++countt;
       ArcNode *p=NULL;
       for(p=G->vertices[i].firstarc;p;p=p->nextarc)
       {
            int k;
            k=p->adjvex;
            if(!(--G->vertices[k].count))//���뽫�뵱ǰ�ڵ������ıߣ���ȼ�1.
                Push(S,k);
       }//end for
    }//end while

    if(countt<G->vexnum)
        return 0;
    else
        return 1;
}//TopoSort

int main()
{
    ALGraph *G;
    CreateALGraph_adjlist(G);
    TopoSort(G);
    return 1;
}
