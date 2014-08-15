#include <stdio.h>
#include <stdlib.h>

void MaxMin(int *array, int n);
void MaxMin2(int i, int j, int max, int min);
void swap(int *n, int *m);
int a[]={0,9,1,5,8,7,789,100,4,6};

int main()
{
    int array[]={7,8,9,1,4,2,5,78,100,3,0};
    int n=sizeof(array)/sizeof(int);
    //MaxMin(array,n);
    int max=0;
    int min=0;
    MaxMin2(1,9,max,min);
    //printf("max=%d; min=%d",max,min);
    return 0;
}
// it's better to use C++ to implement
void MaxMin2(int i, int j, int max, int min)
{
    if(i==j)
        max=min=a[i];
    else if(i==j-1)
    {
        if(a[i]<a[j])
        {
            max=a[j];
            min=a[i];
        }else
        {
            max=a[i];
            min=a[j];
        }
    }
    else
    {
        int max1,min1;
        int mid=(i+j)/2;
        MaxMin2(i,mid,max,min);
        MaxMin2(mid+1,j,max1,min1);

        if(max<max1)
            max=max1;
        if(min>min1)
            min=min1;
    }
    printf("max=%d,min=%d.\n",max,min);

}
void MaxMin(int *array, int n)
{
    int num=0;
    int half=n>>1;
    printf("half=%d\n",half);
    int i=0;
    for(i=0;i<half;i++)
    {
        if(array[i]>array[i+half])
        {
            swap(array[i],array[i+half]);
            num++;
        }
    }
    // 如果n为奇数，则最后剩下一个没有比较，
    // 这时让它与第一个比较，如果比第一个更小，则交换，否则不动，作为最大的部分
    if( (n&1) != 0)
    {
      if(array[0] > array[n-1])
      {
          swap(array[0], array[n-1]);
          num++;
      }

    }

    int min=array[0];
    for(i=1;i<=half;i++)
    {
        if(min>array[i])
        {
           min=array[i];
           num++;
        }
    }
    printf("min=%d\n",min);

    int max=array[half];
    for(i=half+1;i<n;i++)
    {
        if(max<array[i])
        {
           max=array[i];
           num++;
        }
    }
    printf("max=%d\n",max);
    printf("n=%d,num=%d\n",n,num);
}
void swap(int *n, int *m)
{
    int a;
    a=n;
    n=m;
    m=a;
}
