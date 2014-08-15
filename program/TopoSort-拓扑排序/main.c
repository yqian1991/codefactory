#include "stdio.h"
#include "conio.h"
#include "stdlib.h"

#define MAX_VERTEX_NUM 20//最大顶点数
#define STACK_INIT_SIZE 16//栈大小
#define STACKINCREMENT 5

typedef  int SElemType;
typedef char VertexType;

typedef struct
{
    SElemType *base;
    SElemType *top;
    int stacksize;
}SqStack;

//用邻接表来作图的存储结构
typedef struct ArcNode
{
       int adjvex;
       struct ArcNode *nextarc;
       int info;
}ArcNode;  //边表结点类型

//顶点类型
typedef struct VNode
{
       VertexType data;
       int count;
       ArcNode *firstarc;
}VNode,AdjList[MAX_VERTEX_NUM]; //头结点

typedef struct
{
       AdjList vertices;  //邻接表
       int vexnum,arcnum;
}ALGraph;

int InitStack(SqStack *S)
{
    printf("初始化堆栈：\n");
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

    printf("Input Vertices(以回车隔开各个数据),共%d个顶点:\n",G->vexnum);
    for (i=0;i<G->vexnum;i++)
    {
        scanf("%c%c",&enter,&(G->vertices[i].data));//输入顶点
        G->vertices[i].firstarc=NULL;
    }//for

    printf("Input Arcs(v1,v2,w)以回车分开各个数据，共%d条边:\n",G->arcnum);
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
        p->nextarc=G->vertices[i].firstarc; //前插法,即每次都插入到头结点的后面
        G->vertices[i].firstarc=p;
        printf("Next\n");
    }//for
    printf("图建立完毕\n");
}//CreateALGraph_adjlist

//寻找入度
void FindInDegree(ALGraph *G)
{
    printf("***为%d个顶点建立入度数据：\n",G->vexnum);
    int i,j;
    for(i=0;i<G->vexnum;i++)
    {
        G->vertices[i].count=0;//将count（入度）初始化为0
    }//end for
    printf("******入度初始化为0完毕\n");
    for(j=0;j<G->vexnum;j++)
    {
       //calculate indgrees for every Arc node
       /*all the arc in current node should add 1 to its arc's count,
        because current node marks a indegree for all arcs*/
       ArcNode *p=NULL;
       for(p=G->vertices[j].firstarc;p;p=p->nextarc)
         G->vertices[p->adjvex].count++;
    }//end for
    printf("******入度计算完毕\n");
}//end FindInDegree

//拓扑排序主函数
int TopoSort(ALGraph *G)
{
    printf("进行拓扑排序：\n");
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
            if(!(--G->vertices[k].count))//必须将与当前节点相连的边，入度减1.
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
