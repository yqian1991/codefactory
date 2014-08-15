#include <stdio.h>
#include <stdlib.h>

void print(char *str)
{
    int i=0;
    for(i=0;i<strlen(str);i++)
    {
        printf("%c",str[i]);
    }
    printf("\n");
}

int main()
{
    /*char *str=(char*)malloc(100);
    strcpy(str,"hello kitty");
    printf(str);
    free(str);
    if(str!=NULL)
    {
        printf(str);
        strcpy(str,"hello lulu");
    }
    printf(str);*/

    int array[7]={1,2,3,4,5,6,7};
    int *pointer = array;
    printf("%d.\n", *(pointer+6));

    int buff[4][4]={
                    {1,2,3,4},//buff[0][n]
                    {5,6,7,8},//buff[1][n]
                    {9,10,11,12},//buff[2][n]
                    {13,14,15,16}//buff[3][n]
                   };
    int **p=buff;
    printf("%d.\n",*(buff+0)[0]);//第二行
    printf("%d.\n",(*buff+2)[0]);//
    printf("xx:%d.\n",(int *)buff[2]);//第3行的首地址
    //printf("%d.\n", (*(p+2)+1)   );//括号里的在行上，括号外的在列上

    int* pt;
    int b=2;
    pt=&b;
    return 0;
}
