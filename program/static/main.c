#include <stdio.h>
#include <stdlib.h>

static int j;//ȫ���ⲿ��̬����,��ʾ����Ϊ�����ļ�����
void fun1(void)
{
    static int i=0;//�ֲ���̬���������м�����
    i++;
    //printf(" I have been called %d times\n",i);
}

void fun2(void)
{
    printf("j=%d",j);
    j=0;
    printf("j=%d",j);
    j++;
    printf("j=%d",j);
    printf("\n");

}
int main()
{
    int k = 0;
    for(k=0;k<10;k++)
     {
          fun1();
          fun2();
     }
     printf("j=%d",j);
   return 0;
}
