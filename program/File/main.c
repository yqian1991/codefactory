#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE *fp;
    char ch;

    fp=fopen("e:\\data1.txt","r");
    if(fp!=NULL)
    {
        printf("���ļ��Ѿ����ڣ��Ƿ񸲸ǣ�(y/n)");
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
        printf("���ļ�������");
    }
    fclose(fp);

    /*fp=fopen("e:\\data1.txt","w");//�ڶ�������Ϊw����ʾ��д��û���ļ�ʱ�ᴴ���ļ�
    if(fp!=NULL)
        printf("����ļ��Ѿ���������\n");
    else
    {
        printf("����ļ����ܱ�������\n");
        exit(1);
    }
    fclose(fp);*/
    return 0;
}
