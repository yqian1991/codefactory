#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE *fp;
    char ch;

    fp=fopen("e:\\data1.txt","r");
    if(fp!=NULL)
    {
        printf("该文件已经存在，是否覆盖？(y/n)");
        scanf("%c",&ch);
        if(ch=='n'||ch=='N')
        {
            exit(1);
        }else
        {
            printf("ok!!!");
        }

    }else
    {
        printf("该文件不存在");
    }
    fclose(fp);

    /*fp=fopen("e:\\data1.txt","w");//第二个参数为w，表示可写，没有文件时会创建文件
    if(fp!=NULL)
        printf("这个文件已经被创建！\n");
    else
    {
        printf("这个文件不能被创建！\n");
        exit(1);
    }
    fclose(fp);*/
    return 0;
}
