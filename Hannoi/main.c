#include <stdio.h>
#include <stdlib.h>
int number;
void move(int n, char a, char b, char c)
{//将n个盘子从a柱子,经过b，移动到c
    if(n==1)
    {//只剩一个盘子，则从a移动到c，即可
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
    printf("输入盘子数：\n");
    int n=0;
    scanf("%d",&n);
    char a='A',b='B',c='C';
    move(n,a,b,c);
    printf("number=%d.\n",number);
    return 0;
}
