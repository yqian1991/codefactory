#include <stdio.h>
#include <malloc.h>

#define ERROR 0
#define OK 1

typedef int ElemType;

typedef struct LNode
{
    ElemType data;
    struct LNode *next;
} LNode,*LinkList;

//初始化
LinkList ListInit()
{

    LNode *base=(LinkList)malloc(sizeof(LNode));
    base->data=0;
    base->next=NULL;
    return base;
}
//插入一个元素
int ListInsert(LinkList *L,int i,ElemType *e)
{
    LNode *p,*s;
    int j=0;
    p=(LNode *)L;
    while(p&&j<i-1)
    {
        p=p->next;
        ++j;
    }
    if(!p||j>i-1)
        return ERROR;
    s=(LNode *)malloc(sizeof(LNode));
    s->data=e;
    s->next=p->next;
    p->next=s;
    printf("insert to B:%d.\n",e);
    return OK;
}
//删除一个结点i
int ListDelete(LinkList *L, int i, ElemType *e)
{
    LinkList p=L,q;
    int j=0;
    while(p->next&&j<i-1)
    {
        p=p->next;
        ++j;
    }
    if(!(p->next)||j>i-1)
        return ERROR;
    q=p->next;
    p->next=q->next;
    e=q->data;
    printf("delete from B:%d.\n",e);
    free(q);
}
//长度
int ListLength(LinkList L)
{
    LinkList p=L;
    int j=0;
    if(!L)
        return ERROR;
    while(p->next)
    {
        p=p->next;
        ++j;
    }
    return j;
}
//查找一个元素,得到第i个元素，存放在e所指向的内存里
int GetElem(LinkList *L,int i,ElemType *e)
{
    LNode *p=L;
    int j=0;
    while(p->next&&j<i)
    {
        p=p->next;
        ++j;
    }
    if(!p||j>i)
        return ERROR;
    e=p->data;
    //printf("GetElem: e=%d\n",e);
    return e;
}
//输出链表元素
void Display(LinkList L)
{
    LNode *p=L;
    if(!(p->next))
    {
        printf("NULL,");
        return;
    }
    else
        p=p->next;
    while(p)
    {

        printf("%d,",p->data);
        p=p->next;
    }
}
//求幂集
void PowerSet(int i,LinkList A,LinkList B)
{
    int k=0;
    ElemType e=0;

    if(i>ListLength(A))
    {
        Display(B);
        printf("\n");
    }
    else
    {
        e=GetElem(A,i,e);//查找第i个元素，放在e里
        k=ListLength(B);//k为链表B的长度
        ListInsert(B,k+1,e);//将查找到的元素加入到列表B的尾部
        //Display(B);
        PowerSet(i+1,A,B);
        ListDelete(B,k+1,e);
        PowerSet(i+1,A,B);
    }
}

int main(void)
{
    LinkList list=ListInit(); //初始化
    LinkList list2=ListInit();//初始化

    ListInsert(list,1,1);//插入元素
    ListInsert(list,2,2);
    ListInsert(list,3,3);

    Display(list);//输出元素

    printf("\nPower Set is:\n");
    PowerSet(1,list,list2);//求幂集

    return 0;
}
