#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <stdint.h>
#include <string.h>
/*
Ŀ�ģ���������ѣ�Ҳ���Ա��С���ѣ�
���ģ��ѵĵ���
���룺һϵ�������ļ����������ļ��������Կո����
����������
*/

void Swap(uint32_t* array, uint32_t i, uint32_t j)
{
	assert(array);
	uint32_t tmp;
	tmp = array[j];
	array[j] = array[i];
	array[i] = tmp;
}

/*����ѵ���*/
void MaxHeapify(uint32_t* array, uint32_t heapSize, uint32_t currentNode)
{
	uint32_t leftChild, rightChild,  largest;
	leftChild = 2*currentNode + 1;
	rightChild = 2*currentNode + 2;
	if(leftChild < heapSize && array[leftChild] > array[currentNode])
		largest = leftChild;
	else
		largest = currentNode;
	if(rightChild < heapSize && array[rightChild] > array[largest])
		largest = rightChild;
	if(largest != currentNode)
	{
	    Swap(array, largest, currentNode);
		MaxHeapify(array, heapSize, largest);
	}
}

/*���������*/
void MaxHeapCreat(uint32_t* array, uint32_t heapSize)
{
	int i;
	for(i = heapSize/2; i >= 0; i--)
	{
		MaxHeapify(array, heapSize, i);
	}
}

/*С���ѵ���*/
void MinHeapify(uint32_t* array, uint32_t heapSize, uint32_t currentNode)
{
	uint32_t leftChild, rightChild,  minimum;
	leftChild = 2*currentNode + 1;
	rightChild = 2*currentNode + 2;
	if(leftChild < heapSize && array[leftChild] < array[currentNode])
		minimum = leftChild;
	else
		minimum = currentNode;
	if(rightChild < heapSize && array[rightChild] < array[minimum])
		minimum = rightChild;
	if(minimum != currentNode)
	{
	    Swap(array, minimum, currentNode);
		MinHeapify(array, heapSize, minimum);
	}
}
/*����С����*/
void MinHeapCreat(uint32_t* array, uint32_t heapSize)
{
	int i;
	for(i = heapSize/2; i >= 0; i--)
	{
		MinHeapify(array, heapSize, i);
	}
}
int main()
{
	uint32_t tmp;
	uint32_t *array;
	array = (uint32_t*)malloc(sizeof(uint32_t));
	int i, heapSize = 0;

	/*���ļ��ж�������������*/
    char* filePathway = "C:/Users/Administrator/Desktop/data.txt";
    FILE* fp;
	fp = fopen(filePathway, "rb");
	if(!fp)
	{
	    fprintf(stderr, "Can not open file correctly\n");
	}
	while(!feof(fp))
	{
	    fscanf(fp, "%d", &tmp);
	    heapSize++;
	    array = (uint32_t*)realloc(array, sizeof(uint32_t) * (heapSize ));
	    if(array == NULL)
	    {
	        fprintf(stderr, "realloc error!\n");
	        return 1;
	    }
	    array[heapSize - 1] = tmp;
    }
    printf("The origen dataset:\n");
    for(i = 0; i < heapSize; i++)
    {
        printf("%d\t", array[i]);
    }
    printf("\n");

    /*����С���Ѳ����*/
    MinHeapCreat(array, heapSize);
    printf("Output the MinHeap:\n");
    for(i = 0; i < heapSize; i++)
    {
        printf("%d\t", array[i]);
    }
    printf("\n");

    /*��������Ѳ����*/
    MaxHeapCreat(array, heapSize);
    printf("Output the MaxHeap:\n");
    for(i = 0; i < heapSize; i++)
    {
        printf("%d\t", array[i]);
    }
    free(array);
	fclose(fp);

	return 0;
}
