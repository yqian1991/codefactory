#include <malloc.h>
#include "topn.h"

// --------------------------------------------------------------------------------------------- ˽�к����ӿ�
// ����˵�����������µ����ѣ�ֻ�е�һ��Ԫ�ز����������
// ����˵����hp: [IN], topn�Ѷ���
// �� �� ֵ����
static void tpn_adjust_up_down(tpn_heap_t* hp)
{
	int child, child1, child2, parent;	// child1: ���ӣ�child2: �Һ��ӣ�child: ��Ҫ�����ĺ���
	tpn_elem_t tpne;
	parent = 0;
	child1 = parent * 2 + 1;
	child2 = parent * 2 + 2;
	while (child1 < hp->size)
	{
		if (child2 >= hp->size || hp->heap[child1].weight < hp->heap[child2].weight)
		{
			child = child1;
		}
		else
		{
			child = child2;
		}
		if (hp->heap[child].weight > hp->heap[parent].weight)
		{
			break;
		}
		tpne = hp->heap[child];
		hp->heap[child] = hp->heap[parent];
		hp->heap[parent] = tpne;
		parent = child;
		child1 = parent * 2 + 1;
		child2 = parent * 2 + 2;
	}
}

// ����˵�����������ϵ����ѣ�ֻ�����һ��Ԫ�ز����������
// ����˵����hp: [IN], topn�Ѷ���
// �� �� ֵ����
static void tpn_adjust_down_up(tpn_heap_t* hp)
{
	int child, parent;
	tpn_elem_t tpne;

	child = hp->size - 1;	// ���һ��Ԫ��
	parent = (child + 1) / 2 - 1;
	while (parent != -1 && hp->heap[child].weight < hp->heap[parent].weight)
	{
		tpne = hp->heap[child];
		hp->heap[child] = hp->heap[parent];
		hp->heap[parent] = tpne;
		child = parent;
		parent = (child + 1) / 2 - 1;
	}
}

// --------------------------------------------------------------------------------------------- ���к����ӿ�
// ����˵����topn�ѳ�ʼ��
// ����˵����hp: [IN], topn�Ѷ���
//           n: [IN], �ѵ�����������������
// �� �� ֵ���ɹ�����0��ʧ�ܷ��ظ���
int tpn_init(tpn_heap_t* hp, int n)
{
	hp->heap = (tpn_elem_t*)malloc(sizeof(tpn_elem_t) * n);
	if (!(hp->heap))
	{
		return -127;
	}
	hp->n = n;
	hp->size = 0;
	return 0;
}

// ����˵���������Ԫ��
// ����˵����hp: [IN], �Ѷ���
//           elem: [IN], ���Ԫ��
//           priority: [IN], Ȩ��
// �� �� ֵ���ɹ�����0��ʧ�ܷ��ظ���
int tpn_add(tpn_heap_t* hp, void* elem, tpn_weight_t weight)
{
	if (hp->size == hp->n)		// ������
	{
		if (hp->heap[0].weight > weight)	// ��ǰԪ�ص�Ȩ�رȶ��е��κ�һ��Ԫ�ص�Ȩ�ض�С
		{
			return 0;
		}
		hp->heap[0].elem = elem;
		hp->heap[0].weight = weight;
		tpn_adjust_up_down(hp);
	}
	else	// ��δ��
	{
		hp->heap[hp->size].elem = elem;
		hp->heap[hp->size].weight = weight;
		hp->size ++;
		tpn_adjust_down_up(hp);
	}
	return 0;
}

// ����˵������ȡtopnԪ�أ���Ȩ�شӴ�С����
// ����˵����hp: [IN], �Ѷ���
//           buf: [OUT], Ԫ�ػ��������û�����ռ䣬��С������ڵ���n
// �� �� ֵ������������ЧԪ�صĸ�����ʧ�ܷ��ظ���
int tpn_get_topn(tpn_heap_t* hp, tpn_elem_t* buf)
{
	int pos, size;	// buf�е�Ԫ���±�
	size = hp->n < hp->size ? hp->n : hp->size;
	pos = size - 1;
	while (pos >= 0 && hp->size > 0)
	{
		buf[pos] = hp->heap[0];
		hp->heap[0] = hp->heap[hp->size - 1];
		hp->size --;
		tpn_adjust_up_down(hp);
		pos --;
	}
	return size;
}

// ����˵�������topn��
// ����˵����hp: [IN], �Ѷ���
// �� �� ֵ����
void tpn_clear(tpn_heap_t* hp)
{
	hp->size = 0;
}

// ����˵�������ٶ�
// ����˵����hp: [IN], �Ѷ���
// �� �� ֵ����
void tpn_destroy(tpn_heap_t* hp)
{
	if (hp->heap)
	{
		free(hp->heap);
		hp->heap = 0;
	}
}
int main (void)
{

}
