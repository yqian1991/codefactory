#include <stdio.h>
#include <stdlib.h>
/*
*******���嵥ѭ�������ṹ��*********
typedef struct Lnode
*********���������ĺ���*************
void createListF()
*********��ʾ�����ĺ���*************
void List_display(struct Lnode*head)
*******�����ż�����ĺ���***********
void separator(struct Lnode*plyn ,struct Lnode*odd)
*/

//ѭ�������洢�ṹ����
typedef struct Lnode
{
  int data;
  struct Lnode *next;
}Lnode ,*LnodeLink;
typedef LnodeLink cycleList;
struct Lnode *head;//ͷ���

void createListF()
{
    int a[10];//���ܼ�������
    //ѭ�������ṹ��ʼ��
    struct Lnode *q,*p;//p�½ڵ㣬qͷ���
    q=(cycleList)malloc(sizeof(struct Lnode));//����ͷ���洢�ռ�
    q->next=q;//��ѭ�������趨
    head=q;//��ѭ�������趨
    int n=0,i=0;
    printf("�趨�������������������(n<10) n=");
     scanf("%d",&n);
    if(n>10)
    {
      printf("����ʮ�����ˣ�����");
      return 0;
    }
    else
    {
        for(i=0;i<n;i++)
        {
           scanf("%d",&a[i]);//��������
        }
        int b[n];
        int i=n,j=0;
        //����������Ϊ��������˳�򲢴��뵥ѭ������
        for(i=n-1;i>=0;i--)
        {
          b[j]=a[i];
          j++;
        }
        int k=0;
        for(k=0;k<n;k++)
        {
           p=(cycleList)malloc(sizeof(struct Lnode));
           p->data=b[k];
           p->next=q->next;
           q->next=p;
        }
    }
}

//�˺�����ʾѭ��������������ֵ
void List_display(struct Lnode*head)
{
   struct Lnode*p;
   p=head->next;
   while(p!=head)
   {
      printf("%d,",p->data);
      p=p->next;
   }
   printf("\n");
}

//�˺�������ѭ������������ż���ֿ������洢���
void separator(struct Lnode*plyn ,struct Lnode*odd)
{//��ż�������ԭ��ѭ�������ṹ�У�������������½��ĵ�ѭ�������ṹ��
    struct Lnode *q,*p,*s;
    //oddΪ�½��Ĵ��������ѭ��������ͷָ�룬�˴������˿ձ�
    odd=(cycleList)malloc(sizeof(struct Lnode));
    odd->next=odd;
    //plynΪԭ��ѭ��������ͷָ��
    q=plyn;
    p=plyn->next;
    s=odd;//sָ���������������β�ڵ�
    while(p!=plyn)
    {
        if((p->data)%2==0)//��ż��
        {
            q=p;
            p=p->next;
        }else{
            q->next=p->next;//��ԭ������ɾ���������
            //�����������±���
            p->next=s->next;
            s->next=p;
            //ָ������ƶ�
            p=q->next;
            s=s->next;
        }
    }
    //��ӡ����ż����ѭ������������
    printf("ż��Ϊ��");
    List_display(plyn);
    printf("����Ϊ��");
    List_display(odd);
}
int main()
{
    struct Lnode*odd;
    createListF();
    printf("���������������Ϊ��");
    List_display(head);
    separator(head,odd);//����ż���ֿ�������ӡ���
    return 0;
}