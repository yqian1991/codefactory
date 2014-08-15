//MinHeap.h
#ifndef MINHEAP_H
#define MINHEAP_H

#include<stdlib.h>
#include<iostream>
using namespace std;

template<class Type> class MinHeap
{
public:
	MinHeap(int maxSize);			//���캯���������ն�
	MinHeap(Type a[], int n);		//���캯����������a[]��ֵ������
	~MinHeap()
	{
		delete [] heapArr;
	}
	int Insert(const Type &d);		//�ڶ��в���Ԫ��d
	Type DeleteTop();				//ɾ���Ѷ�Ԫ��
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
	void Show();					//˳����ʾ����
private:
	Type *heapArr;					//��Ŷ�������Ԫ�ص�����
	int heapCurrentSize;			//���е�ǰ����Ԫ����Ŀ
	int heapMaxSize;				//��������Ԫ�ص������Ŀ
	void FilterDown(int p);			//���µ���ʹ�Խ��pΪ����������Ϊ��
	void FilterUp(int p);			//
};

template<class Type> void MinHeap<Type>::FilterDown(const int start)
{//���µ���ʹ��start��ʼ��heapCurrentSize-1Ϊֹ�������г�Ϊ��С��
	int i=start, j;
	Type temp=heapArr[i];
	j=2*i+1;						//jΪi������
	while(j<=heapCurrentSize-1)
	{
		if(j<heapCurrentSize-1&&heapArr[j].key>heapArr[j+1].key)
			j++;					//�����Һ�����ѡ�ؼ��ֽ�С��
		if(temp.key<=heapArr[j].key)
			break;					//break����ʡ������������������ֱ������ѭ��
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
{//��p��ʼ���ϵ�����ʹ���г�Ϊ��
	int j=p, i;
	Type temp=heapArr[j];
	i=(j-1)/2;						//i��j��˫��
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
		cerr<<"�ѵĴ�С����С��1"<<endl;
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
		cerr<<"�ѵĴ�С����С��1"<<endl;
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
		cout<<"������"<<endl;
		return 0;
	}
	heapArr[heapCurrentSize]=d;			//�ڶ�β��������Ԫ��d
	FilterUp(heapCurrentSize);			//���ϵ���Ϊ��
	heapCurrentSize++;					//��Ԫ����Ŀ��1
	return 1;
}

template<class Type> Type MinHeap<Type>::DeleteTop()
{
	if(IsEmpty())
	{
		cout<<"���ѿ�"<<endl;
		return NULL;
	}
	Type temp=heapArr[0];
	heapArr[0]=heapArr[heapCurrentSize-1];//��ĩԪ�����Ƶ��Ѷ�
	heapCurrentSize--;
	FilterDown(0);
	return temp;
}

template<class Type> void MinHeap<Type>::Show()
{
	if(IsEmpty())
	{
		cout<<"���ѿ�"<<endl;
		return;
	}
	cout<<heapArr[0].key;
	for(int i=1; i<heapCurrentSize; i++)
		cout<<" "<<heapArr[i].key;
	cout<<endl;
}

#endif
