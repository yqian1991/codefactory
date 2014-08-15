#include <malloc.h>
#include "topn.h"

// --------------------------------------------------------------------------------------------- 私有函数接口
// 功能说明：从上往下调整堆，只有第一个元素不满足堆条件
// 参数说明：hp: [IN], topn堆对象
// 返 回 值：无
static void tpn_adjust_up_down(tpn_heap_t* hp)
{
	int child, child1, child2, parent;	// child1: 左孩子，child2: 右孩子，child: 需要交换的孩子
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

// 功能说明：从下往上调整堆，只有最后一个元素不满足堆条件
// 参数说明：hp: [IN], topn堆对象
// 返 回 值：无
static void tpn_adjust_down_up(tpn_heap_t* hp)
{
	int child, parent;
	tpn_elem_t tpne;

	child = hp->size - 1;	// 最后一个元素
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

// --------------------------------------------------------------------------------------------- 公有函数接口
// 功能说明：topn堆初始化
// 参数说明：hp: [IN], topn堆对象
//           n: [IN], 堆的容量，该容量不变
// 返 回 值：成功返回0，失败返回负数
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

// 功能说明：添加新元素
// 参数说明：hp: [IN], 堆对象
//           elem: [IN], 入堆元素
//           priority: [IN], 权重
// 返 回 值：成功返回0，失败返回负数
int tpn_add(tpn_heap_t* hp, void* elem, tpn_weight_t weight)
{
	if (hp->size == hp->n)		// 堆已满
	{
		if (hp->heap[0].weight > weight)	// 当前元素的权重比堆中的任何一个元素的权重都小
		{
			return 0;
		}
		hp->heap[0].elem = elem;
		hp->heap[0].weight = weight;
		tpn_adjust_up_down(hp);
	}
	else	// 堆未满
	{
		hp->heap[hp->size].elem = elem;
		hp->heap[hp->size].weight = weight;
		hp->size ++;
		tpn_adjust_down_up(hp);
	}
	return 0;
}

// 功能说明：获取topn元素，按权重从大到小排序
// 参数说明：hp: [IN], 堆对象
//           buf: [OUT], 元素缓冲区，用户分配空间，大小必须大于等于n
// 返 回 值：缓冲区中有效元素的个数，失败返回负数
int tpn_get_topn(tpn_heap_t* hp, tpn_elem_t* buf)
{
	int pos, size;	// buf中的元素下标
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

// 功能说明：清空topn堆
// 参数说明：hp: [IN], 堆对象
// 返 回 值：无
void tpn_clear(tpn_heap_t* hp)
{
	hp->size = 0;
}

// 功能说明：销毁堆
// 参数说明：hp: [IN], 堆对象
// 返 回 值：无
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
