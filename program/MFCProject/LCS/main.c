#include<stdio.h>
#include<string.h>
int lcs_length(char x[], char y[]);
int main()
{
    char x[100],y[100];
    int len;
    while(1)
    {
        scanf("%s%s",x,y);
        if(x[0]=='0') //Լ����һ���ַ����ԡ�0����ʼ��ʾ����
        break;
        len=lcs_length(x,y);
        printf("%d\n",len);
    }
}
int lcs_length(char x[], char y[] )
{
    int m,n,i,j,l[100][100];
    m=strlen(x);
    n=strlen(y);
    for(i=0;i<m+1;i++)
     l[i][0]=0;
    for(j=0;j<n+1;j++)
     l[0][j]=0;
    for(i=1;i<=m;i++)
     for(j=1;j<=n;j++)
     if(x[i-1]==y[j-1]) //i,j��1��ʼ�����ַ����Ǵ�0��ʼ
      l[i][j]=l[i-1][j-1]+1;
     else if(l[i][j-1]>l[i-1][j])
      l[i][j]=l[i][j-1];
     else
      l[i][j]=l[i-1][j];
    return l[m][n];
}

