////////////////////////////////////////////////////////////////////////////////////////////////////
//
// ����˵�������ȼ����У����ö�ʵ��
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef _H_PRIORITYQUEUE_JGDUAN_20070827
#define _H_PRIORITYQUEUE_JGDUAN_20070827

#ifdef __cplusplus
extern "C" {
#endif

typedef float tpn_weight_t;	// Ȩ��

typedef struct tpn_elem_t	// topn�ڵ�����
{
	void* elem;	// Ԫ��
	tpn_weight_t weight;	// Ȩ��
} tpn_elem_t;

typedef struct tpn_heap_t	// topn��
{
	tpn_elem_t* heap;	// topn�����飬С����
	int size;	// ��ǰ����Ԫ�ص�����
	int n;	// topn�е�n
} tpn_heap_t;

// ����˵����topn�ѳ�ʼ��
// ����˵����hp: [IN], topn�Ѷ���
//           n: [IN], �ѵ�����������������
// �� �� ֵ���ɹ�����0��ʧ�ܷ��ظ���
int tpn_init(tpn_heap_t* hp, int n);

// ����˵���������Ԫ��
// ����˵����hp: [IN], �Ѷ���
//           elem: [IN], ���Ԫ��
//           priority: [IN], Ȩ��
// �� �� ֵ���ɹ�����0��ʧ�ܷ��ظ���
int tpn_add(tpn_heap_t* hp, void* elem, tpn_weight_t weight);

// ����˵������ȡtopnԪ�أ���Ȩ�شӴ�С����
// ����˵����hp: [IN], �Ѷ���
//           buf: [OUT], Ԫ�ػ��������û�����ռ䣬��С������ڵ���n
// �� �� ֵ������������ЧԪ�صĸ�����ʧ�ܷ��ظ���
int tpn_get_topn(tpn_heap_t* hp, tpn_elem_t* buf);

// ����˵�������topn��
// ����˵����hp: [IN], �Ѷ���
// �� �� ֵ����
void tpn_clear(tpn_heap_t* hp);

// ����˵�������ٶ�
// ����˵����hp: [IN], �Ѷ���
// �� �� ֵ����
void tpn_destroy(tpn_heap_t* hp);

#ifdef __cplusplus
}
#endif

#endif
