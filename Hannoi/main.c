#include <stdio.h>
#include <stdlib.h>
int number;
void move(int n, char a, char b, char c)
{//��n�����Ӵ�a����,����b���ƶ���c
    if(n==1)
    {//ֻʣһ�����ӣ����a�ƶ���c������
        printf("%c-->%c.\n",a,c);
        number++;
    }
    else
    {
        move(n-1,a,c,b);
        printf("%c-->%c.\n",a,c);
        number++;
        move(n-1,b,a,c);
    }
}
void nonRecursive()
{

}
int main()
{
    printf("������������\n");
    int n=0;
    scanf("%d",&n);
    char a='A',b='B',c='C';
    move(n,a,b,c);
    printf("number=%d.\n",number);
    return 0;
}
