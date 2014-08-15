#include <stdio.h>

int bsearch(int *a, int b, int i, int j);
int bsearch2(int *a, int b);

int main(void)
{
    int a[]={0,1,2,3,4,5,6,7,8,9};
    int result = bsearch(a,120,0,9);
    //int result = bsearch2(a,11);
    if(result == 1)
        printf("yes");
    else
        printf("no");
    return 0;
}

int bsearch(int *a, int b,int i, int j)
{
    if(i<j)
    {
        //int n=i+(j-i)/2;
        int n = (i+j) >> 1;
        if(b<a[n])
        {
            j=n-1;
            bsearch(a,b,i,j);
        }
        else if(b>a[n])
        {
            i=n+1;
            bsearch(a,b,i,j);
        }
        else if(b==a[n])
        {
            return 1;
        }
    }else{
        return 0;
    }
}
int bsearch2(int *a, int b)
{
    int mid = 0;
    int low=0, high = 9;
    while(low<=high)
    {
        mid=low+(high-low)/2;
        if(a[mid] == b ) return 1;
        if(a[mid]<b) low = mid+1;
        else low = mid-1;
    }
    return 0;
}
