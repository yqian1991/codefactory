#include<stdio.h>
#include<stdlib.h>

int main()
{
    int *a,*b,m,n,x,i,k,z;
    scanf("%d",&m);
    b=(int*)malloc(m*sizeof(int));
    a=(int*)malloc(m*sizeof(int));
    for(i=0; i<m; i++)
    {
        scanf("%d ",&a[i]);
    }
    scanf("%d",&n);
    x=n%m;

    if(x!=0)
    {
        for(int j=x-1; j<m-1; j++)
        {
            a[j]=a[j+1];
        }
        for( i=0; i<m-1; i++)
            for(k=0; k<m-i-1; k++)
                if(a[k]>a[k+1])
                {
                    n=a[k];
					.
                    a[k]=a[k+1];
                    a[k+1]=n;
                }
        for(z=0; z<m-1; z++)
        {
            printf("%d",a[z]);
            if(z<m-2)
            {
                printf(" ");
            }
        }
    }
    else

    {
        for(i=0; i<m-1; i++)
        {
            b[i]=a[i];
        }
        for(i=0; i<m-1; i++)
            for(k=0; k<m-i-1; k++)
                if(b[k]>b[k+1])
                {
                    n=b[k];
                    b[k]=b[k+1];
                    b[k+1]=n;
                }
        for(z=0; z<m-1; z++)
            printf("%d ",b[z]);
    }
    printf("\n");
    free(a);
    free(b);
    return 0;
}
