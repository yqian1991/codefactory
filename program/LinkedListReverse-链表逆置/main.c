#include<stdio.h>
#include "defs.h"

void add(node*p)
{
    node *p1,*p2;
    p1=head;
    p2=p1;
    while(p2)
    {
        p1=p2;
        p2=p2->next;
    }
    p1->next=p;
    p->next=p2;
}

void show(node *p)
{
    while(p)
        printf("%d",p->id);
        p=p->next;
}

//һ�����õ�����ķ���
node* rev(node *head)
{//��ȡ��һ��Ԫ�ص�ָ�룬Ȼ�����ڵĽڵ����������ʵ������
    node *prev=NULL,*next=NULL;
    while(head)
    {
        next=head->next;
        head->next=prev;
        prev=head;
        head=next;
    }
    return prev;
}

//��һ�����õ�����ķ���
node * rev2(node *head)//�ݹ鷽ʽ������������
{
    if(head==NULL||head->next==NULL)
        return head;
    node *tail=rev2(head->next);
    head->next->next=head;
    head->next=NULL;
    return tail;
}

//���������õ�����ķ���
node *rev3(node *head)
{
     node *p1,*p2,*tail=NULL,*newhead=NULL;
     //node *temp;
     if(head==NULL)
       return NULL;
     if(head->next==NULL)
      return head;
     if(head->next->next==NULL)
     {
      newhead=head->next;
      head->next=NULL;
      newhead->next=head;
      return newhead;
     }
    do
    {
         p2=NULL;
         p1=head;
         while(p1->next!=NULL)
         {
          p2=p1;
          p1=p1->next;
         }
         if(newhead==NULL)
         {
           newhead=p1;
           //temp=newhead->next=p2;
           tail=newhead->next=p2;
           tail->next=NULL;
         }
         else
         {
            tail->next=p1;
            tail=p1;
         }
        //temp=temp->next=p2;
         p2->next=NULL;

       }while(head->next!=NULL);

       tail->next=head;

       return(newhead);
}
int main(void)
{
            head->next=NULL;

            node *p1 = NULL;
            p1->id=7;
            add(p1);

            node *p2 = NULL;
            p2->id=7;
            add(p2);

            node *p3 = NULL;
            p3->id=7;
            add(p3);

            printf("�����\n");
            show(head->next);
            printf("���ú������\n");
            show(rev(head->next));//rev2 rev3������ʹ��

            return 0;
}
