#include <stdio.h>
#include <stdlib.h>
/*
*******定义单循环链表结构体*********
typedef struct Lnode
*********创建链表的函数*************
void createListF()
*********显示链表的函数*************
void List_display(struct Lnode*head)
*******拆分奇偶链表的函数***********
void separator(struct Lnode*plyn ,struct Lnode*odd)
*/

//循环链表存储结构定义
typedef struct Lnode
{
  int data;
  struct Lnode *next;
}Lnode ,*LnodeLink;
typedef LnodeLink cycleList;
struct Lnode *head;//头结点

void createListF()
{
    char ch;//接受键盘输入
    //循环链表结构初始化
    struct Lnode *q,*p;//p新节点，q头结点
    q=(cycleList)malloc(sizeof(struct Lnode));//分配头结点存储空间
    q->next=q;//单循环链表设定
    head=q;//单循环链表设定
    while((ch=getchar())!='\n')
    {

        p=(cycleList)malloc(sizeof(struct Lnode));
        p->data=ch;
        p->next=q->next;
        q->next=p;
    }
}

//此函数显示循环链表的所有数值
void List_display(struct Lnode*head)
{
   struct Lnode*p;
   p=head->next;
   while(p!=head)
   {
      printf("%c",p->data);
      p=p->next;
   }
   printf("\n");
}

//此函数将单循环链表中奇数偶数分开，并存储结果
void separator(struct Lnode*plyn ,struct Lnode*odd)
{//将偶数存放在原单循环链表结构中，将奇数存放在新建的单循环链表结构中
    struct Lnode *q,*p,*s;
    //odd为新建的存放奇数单循环链表的头指针，此处建立此空表
    odd=(cycleList)malloc(sizeof(struct Lnode));
    odd->next=odd;
    //plyn为原单循环链表的头指针
    q=plyn;
    p=plyn->next;
    s=odd;//s指向奇数结点链表的尾节点
    while(p!=plyn)
    {
        if((p->data)%2==0)//是偶数
        {
            q=p;
            p=p->next;
        }else{
            q->next=p->next;//从原链表中删除奇数结点
            //将奇数插入新表中
            p->next=s->next;
            s->next=p;
            //指针向后移动
            p=q->next;
            s=s->next;
        }
    }
    //打印奇数偶数单循环链表分离结果
    printf("偶数为：");
    List_display(plyn);
    printf("奇数为：");
    List_display(odd);
}
int main()
{
    struct Lnode*odd;
    createListF();
    printf("键盘输入的有序数为：");
    List_display(head);
    separator(head,odd);//奇数偶数分开，并打印结果
    return 0;
}
