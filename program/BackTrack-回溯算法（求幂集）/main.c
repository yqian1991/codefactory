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

//��ʼ��
LinkList ListInit()
{

    LNode *base=(LinkList)malloc(sizeof(LNode));
    base->data=0;
    base->next=NULL;
    return base;
}
//����һ��Ԫ��
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
//ɾ��һ�����i
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
//����
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
//����һ��Ԫ��,�õ���i��Ԫ�أ������e��ָ����ڴ���
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
//�������Ԫ��
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
//���ݼ�
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
        e=GetElem(A,i,e);//���ҵ�i��Ԫ�أ�����e��
        k=ListLength(B);//kΪ����B�ĳ���
        ListInsert(B,k+1,e);//�����ҵ���Ԫ�ؼ��뵽�б�B��β��
        //Display(B);
        PowerSet(i+1,A,B);
        ListDelete(B,k+1,e);
        PowerSet(i+1,A,B);
    }
}

int main(void)
{
    LinkList list=ListInit(); //��ʼ��
    LinkList list2=ListInit();//��ʼ��

    ListInsert(list,1,1);//����Ԫ��
    ListInsert(list,2,2);
    ListInsert(list,3,3);

    Display(list);//���Ԫ��

    printf("\nPower Set is:\n");
    PowerSet(1,list,list2);//���ݼ�

    return 0;
}
