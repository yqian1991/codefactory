////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 功能说明：优先级队列，采用堆实现
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef _H_PRIORITYQUEUE_JGDUAN_20070827
#define _H_PRIORITYQUEUE_JGDUAN_20070827

#ifdef __cplusplus
extern "C" {
#endif

typedef float tpn_weight_t;	// 权重

typedef struct tpn_elem_t	// topn节点类型
{
	void* elem;	// 元素
	tpn_weight_t weight;	// 权重
} tpn_elem_t;

typedef struct tpn_heap_t	// topn堆
{
	tpn_elem_t* heap;	// topn堆数组，小根堆
	int size;	// 当前堆中元素的数量
	int n;	// topn中的n
} tpn_heap_t;

// 功能说明：topn堆初始化
// 参数说明：hp: [IN], topn堆对象
//           n: [IN], 堆的容量，该容量不变
// 返 回 值：成功返回0，失败返回负数
int tpn_init(tpn_heap_t* hp, int n);

// 功能说明：添加新元素
// 参数说明：hp: [IN], 堆对象
//           elem: [IN], 入堆元素
//           priority: [IN], 权重
// 返 回 值：成功返回0，失败返回负数
int tpn_add(tpn_heap_t* hp, void* elem, tpn_weight_t weight);

// 功能说明：获取topn元素，按权重从大到小排序
// 参数说明：hp: [IN], 堆对象
//           buf: [OUT], 元素缓冲区，用户分配空间，大小必须大于等于n
// 返 回 值：缓冲区中有效元素的个数，失败返回负数
int tpn_get_topn(tpn_heap_t* hp, tpn_elem_t* buf);

// 功能说明：清空topn堆
// 参数说明：hp: [IN], 堆对象
// 返 回 值：无
void tpn_clear(tpn_heap_t* hp);

// 功能说明：销毁堆
// 参数说明：hp: [IN], 堆对象
// 返 回 值：无
void tpn_destroy(tpn_heap_t* hp);

#ifdef __cplusplus
}
#endif

#endif
