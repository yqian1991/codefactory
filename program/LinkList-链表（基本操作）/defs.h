#ifndef DEFS_H_INCLUDED
#define DEFS_H_INCLUDED

typedef int elemType;

typedef struct SNode Node;

/************************************************************************/
struct SNode{    /* ���嵥���������� */
    elemType element;
    Node *next;
};
/************************************************************************/
/*             �����ǹ������Ա����Ӵ洢��������������18���㷨        */

/* 1.��ʼ�����Ա����õ�����ı�ͷָ��Ϊ�� */
void initList(Node *pNode);
/* 2.�������Ա��˺������븺����ֹ��ȡ����*/
Node *creatList(Node *pHead);
/* 3.��ӡ��������ı���*/
void printList(Node *pHead);
/* 4.������Ա�L�е�����Ԫ�أ����ͷŵ�����L�����еĽ�㣬ʹ֮��Ϊһ���ձ� */
void clearList(Node *pHead);
/* 5.���ص�����ĳ��� */
int sizeList(Node *pHead);
/* 6.��鵥�����Ƿ�Ϊ�գ���Ϊ���򷵻أ������򷵻أ� */
int isEmptyList(Node *pHead);
/* 7.���ص������е�pos������е�Ԫ�أ���pos������Χ����ֹͣ�������� */
elemType getElement(Node *pHead, int pos);
/* 8.�ӵ������в��Ҿ��и���ֵx�ĵ�һ��Ԫ�أ������ҳɹ��򷵻ظý��data��Ĵ洢��ַ�����򷵻�NULL */
elemType *getElemAddr(Node *pHead, elemType x);
/* 9.�ѵ������е�pos������ֵ�޸�Ϊx��ֵ�����޸ĳɹ����أ������򷵻أ� */
int modifyElem(Node *pNode,int pos,elemType x);
/* 10.������ı�ͷ����һ��Ԫ�� */
int insertHeadList(Node **pNode,elemType insertElem);
/* 11.�������ĩβ���һ��Ԫ�� */
int insertLastList(Node **pNode,elemType insertElem);
/* 12.�������е�pos�����λ�ò���Ԫ��Ϊx�Ľ�㣬������ɹ����أ������򷵻أ� */
/* 13.�����������в���Ԫ��x��㣬ʹ�ò������Ȼ���� */
/* 14.�ӵ�������ɾ����ͷ��㣬���Ѹý���ֵ���أ���ɾ��ʧ����ֹͣ�������� */
/* 15.�ӵ�������ɾ����β��㲢��������ֵ����ɾ��ʧ����ֹͣ�������� */
/* 16.�ӵ�������ɾ����pos����㲢��������ֵ����ɾ��ʧ����ֹͣ�������� */
/* 17.�ӵ�������ɾ��ֵΪx�ĵ�һ����㣬��ɾ���ɹ��򷵻�1,���򷵻�0 */
/* 18.����2��Ԫ�ص�λ�� */
/* 19.�����Ա���п������� */


#endif // DEFS_H_INCLUDED
