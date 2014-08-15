//MinHeap.h
#ifndef MINHEAP_H
#define MINHEAP_H

#include<stdlib.h>
#include<iostream>
using namespace std;

template<class Type> class MinHeap
{
public:
	MinHeap(int maxSize);			//构造函数，建立空堆
	MinHeap(Type a[], int n);		//构造函数，以数组a[]的值建立堆
	~MinHeap()
	{
		delete [] heapArr;
	}
	int Insert(const Type &d);		//在堆中插入元素d
	Type DeleteTop();				//删除堆顶元素
	Type GetTop() const
	{
		return heapArr[0];
	}
	int IsEmpty() const
	{
		return heapCurrentSize==0;
	}
	int IsFull() const
	{
		return heapCurrentSize==heapMaxSize;
	}
	int SizeofHeap() const
	{
		return heapCurrentSize;
	}
	void SetEmpty()
	{
		heapCurrentSize=0;
	}
	void Show();					//顺序显示数组
private:
	Type *heapArr;					//存放堆中数据元素的数组
	int heapCurrentSize;			//堆中当前数据元素数目
	int heapMaxSize;				//堆中数据元素的最大数目
	void FilterDown(int p);			//向下调整使以结点p为根的子树成为堆
	void FilterUp(int p);			//
};

template<class Type> void MinHeap<Type>::FilterDown(const int start)
{//向下调整使从start开始到heapCurrentSize-1为止的子序列成为最小堆
	int i=start, j;
	Type temp=heapArr[i];
	j=2*i+1;						//j为i的左孩子
	while(j<=heapCurrentSize-1)
	{
		if(j<heapCurrentSize-1&&heapArr[j].key>heapArr[j+1].key)
			j++;					//在左右孩子中选关键字较小者
		if(temp.key<=heapArr[j].key)
			break;					//break不能省，如果不需调整，就能直接跳出循环
		else
		{
			heapArr[i]=heapArr[j];
			i=j;
			j=2*j+1;
		}
	}
	heapArr[i]=temp;
}

template<class Type> void MinHeap<Type>::FilterUp(int p)
{//从p开始向上调整，使序列成为堆
	int j=p, i;
	Type temp=heapArr[j];
	i=(j-1)/2;						//i是j的双亲
	while(j>0)
	{
		if(heapArr[i].key<=temp.key)
			break;
		else
		{
			heapArr[j]=heapArr[i];
			j=i;
			i=(j-1)/2;
		}
	}
	heapArr[j]=temp;
}

template<class Type> MinHeap<Type>::MinHeap(int maxSize)
{
	if(maxSize<=0)
	{
		cerr<<"堆的大小不能小于1"<<endl;
		exit(1);
	}
	heapMaxSize=maxSize;
	heapArr=new Type [heapMaxSize];
	heapCurrentSize=0;
}

template<class Type> MinHeap<Type>::MinHeap(Type a[], int n)
{
	if(n<=0)
	{
		cerr<<"堆的大小不能小于1"<<endl;
		exit(1);
	}
	heapMaxSize=n;
	heapArr=new Type [heapMaxSize];
	heapArr=a;
	heapCurrentSize=n;
	int i=(heapCurrentSize-2)/2;
	while(i>=0)
	{
		FilterDown(i);
		i--;
	}
}

template<class Type> int MinHeap<Type>::Insert(const Type &d)
{
	if(IsFull())
	{
		cout<<"堆已满"<<endl;
		return 0;
	}
	heapArr[heapCurrentSize]=d;			//在堆尾插入数据元素d
	FilterUp(heapCurrentSize);			//向上调整为堆
	heapCurrentSize++;					//堆元素数目加1
	return 1;
}

template<class Type> Type MinHeap<Type>::DeleteTop()
{
	if(IsEmpty())
	{
		cout<<"堆已空"<<endl;
		return NULL;
	}
	Type temp=heapArr[0];
	heapArr[0]=heapArr[heapCurrentSize-1];//堆末元素上移到堆顶
	heapCurrentSize--;
	FilterDown(0);
	return temp;
}

template<class Type> void MinHeap<Type>::Show()
{
	if(IsEmpty())
	{
		cout<<"堆已空"<<endl;
		return;
	}
	cout<<heapArr[0].key;
	for(int i=1; i<heapCurrentSize; i++)
		cout<<" "<<heapArr[i].key;
	cout<<endl;
}

#endif
