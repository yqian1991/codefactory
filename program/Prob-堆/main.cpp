//main.cpp
#include"MinHeap.h"

class node
{
public:
	node(int temp=0)
	{
		key=temp;
	}
	void operator=(int temp)
	{
		key=temp;
	}
public:
	int key;
};


int main()
{
/**********************************************/
	MinHeap<node> heap(10);
	node a(12), b(45), c(6), d(23), e(32), f(11), g(5), h(93);
	heap.Insert(a);
	heap.Insert(b);
	heap.Insert(c);
	heap.Insert(d);
	heap.Insert(e);
	heap.Insert(f);
	heap.Insert(g);
	heap.Insert(h);

	heap.Show();

/***********************************************/
	node *node2=new node [8];				//MinHeap类内部有指针赋值操作，需申请堆空间
	node2[0]=12;	node2[1]=45;
	node2[2]=6;		node2[3]=23;
	node2[4]=32;	node2[5]=11;
	node2[6]=5;		node2[7]=93;

	MinHeap<node> heap2(node2, 8);

	heap2.Show();

	delete [] node2;

	return 0;
}
