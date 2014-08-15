#include <stdio.h>
#include <stdlib.h>
#include "sort.h"
int main()
{
    int arr[]={5,9,4,6,8,0,2,10};
    //insertSortD(arr,8);
    //print(arr,8);
    //insertSortA(arr,8);
    //print(arr,8);
    int tmpArray[8] ={0};
    mergeSort(arr, tmpArray, 0, 7);
    print(arr,8);
    return 0;
}
//降序排列
void insertSortD(int array[],int n)
{//默认第一个元素有序，将后面的元素插入到已经排好序的前面的元素中
    int i=0,j=0;
    //int length = sizeof(array)/sizeof(array[0]);
    for(i=1;i<n;i++)
    {
        for(j=0;j<i;j++)
        {
            if(array[j]<=array[i])
            {
                swap(array,i,j);
            }
        }

    }

}
//升序排列
void insertSortA(int array[],int n)
{//默认第一个元素有序，将后面的元素插入到已经排好序的前面的元素中
    int i=0,j=0;
    //int length = sizeof(array)/sizeof(array[0]);
    for(i=1;i<n;i++)
    {
        for(j=0;j<i;j++)
        {
            if(array[j]>=array[i])
            {
                swap(array,i,j);
            }
        }

    }

}
void selectSortD(int array[],int n)
{
    int i=0,j=0;

    for(i=0;i<n;i++)
    {
        int max_position = i;
        for(j=i+1;j<n;j++)
        {
            if(array[max_position]<array[j])
            {
                max_position = j;
            }
        }
        if(max_position!=i)
        {
            swap(array,i,max_position);
        }
    }

}
void selectSortA(int array[],int n)
{
    int i=0,j=0;

    for(i=0;i<n;i++)
    {
        int min_position = i;
        for(j=i+1;j<n;j++)
        {
            if(array[min_position]>array[j])
            {
                min_position = j;
            }
        }
        if(min_position!=i)
        {
            swap(array,i,min_position);
        }
    }

}
void bubbleSortD(int array[], int n)
{
    int i=0,j=0;
    for(i=0;i<n;i++)
    {
        for(j=0;j<n-i-1;j++)
        {
            if(array[j]<array[j+1])
            {
                swap(array,j,j+1);
            }
        }
    }
}
void bubbleSortA(int array[], int n)
{
    int i=0,j=0;
    for(i=0;i<n;i++)
    {
        for(j=0;j<n-i-1;j++)
        {
            if(array[j]>array[j+1])
            {
                swap(array,j,j+1);
            }
        }
    }

}
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
void mergeSort(int array[], int tmpArray[], int left, int right)
{
    if (left < right) {
            int center = (left + right) / 2;
            mergeSort(array, tmpArray, left, center);
            mergeSort(array, tmpArray, center + 1, right);
            merge(array, tmpArray, left, center + 1, right);
    }
}
void merge(int array[],int tmpArray[],int leftPos,int rightPos,int rightEnd)
{
     int i;
     int leftEnd = rightPos - 1;
     int tmpPos = leftPos;
     int numElements = rightEnd - leftPos + 1;
     //two part: [leftPos]-[rightPos-1|leftEnd]  [rightPos]-[rightEnd]
    // Main loop
     while (leftPos <= leftEnd && rightPos <= rightEnd)
            if (array[leftPos] <= (array[rightPos]))
                tmpArray[tmpPos++] = array[leftPos++];
            else
                tmpArray[tmpPos++] = array[rightPos++];

        while (leftPos <= leftEnd)
            // Copy rest of first half
            tmpArray[tmpPos++] = array[leftPos++];

        while (rightPos <= rightEnd)
            // Copy rest of right half
            tmpArray[tmpPos++] = array[rightPos++];

        // Copy tmpArray back
        for (i = 0; i < numElements; i++, rightEnd--)
            array[rightEnd] = tmpArray[rightEnd];
}
void swap(int array[],int i, int j)
{
    int temp=0;
    temp = array[i];
    array[i] = array[j];
    array[j] = temp;
}
void print(int array[],int n)
{
    int i= 0;
    //int length = sizeof(array)/sizeof(array[0]);

    for(i=0;i<n;i++)
    {
        printf("%d ",array[i]);
    }
    printf("\n");
}

int length(int array[])
{
    int length=0;
    int *p =array;
    while(*p!='\0')
    {
        p++;
        length++;

    }
    printf("%d",length);
    return length;
}
