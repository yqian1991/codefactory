#include <stdio.h>

int bsearch(int *a, int b, int i, int j);

int main(void)
{
    int a[]={0,1,2,3,4,5,6,7,8,9};
    int result = bsearch(a,0,0,9);
    if(result == 1)
        printf("yes");
    else
        printf("no");
    return 0;
}

int bsearch(int *a, int b,int i, int j)
{
    int n=(i+j)/2;
    if(b<a[n])
    {
        j=n;
        bsearch(a,b,i,j);
    }
    else if(b>a[n])
    {
        i=n;
        bsearch(a,b,i,j);
    }
    else if(b==a[n])
    {
        return 1;
    }
}
