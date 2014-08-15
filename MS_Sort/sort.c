#include "sort.h"
#include <stdio.h>
#include <stdlib.h>

void quickSortD(int array[],int low ,int high)
{
    if(low<high)
    {
        int piv = partition(array,low,high);
        quickSortD(array,low,piv-1);
        quickSortD(array,piv+1,high);
    }

}
int partition(int array[],int low,int high)
{
    int i=low,j=high;
    int key=array[low];

    while(i!=j)
    {
        while(array[j]>key)
        {//从j开始向前搜索，找到第一个小于key的，交换之
            j--;
        }
        int temp=array[j];
        array[j]=key;
        key=temp;

        while(array[i]<key)
        {//从j开始向前搜索，找到第一个小于key的，交换之
            i++;
        }
        int temp1=array[i];
        array[i]=key;
        key=temp1;

    }
    return i;
}
