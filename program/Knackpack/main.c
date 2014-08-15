# include<stdio.h>
# include<string.h>

int date[1005];

int f(int w,int s)
{
    if(w==0)
        return 1;//正好
    if( ((w<0)||(w>0))&&(s==0) )
        return 0;
    if(f(w-date[s],s-1))
        return 1;//退出来再选下一个
    return f(w,s-1);//选择下一个
}

int main()
{
    int i,Weight,n;
    while(scanf("%d %d",&Weight,&n)!=EOF)
    {
        memset(date,0,sizeof(date));
        for(i=1;i<=n;i++)
            scanf("%d",&date[i]);
        if(f(Weight,n))
            printf("YES\n");
        else printf("NO\n");
    }
    return 0;
}

