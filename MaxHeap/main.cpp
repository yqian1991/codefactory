#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <stdint.h>
#include <string.h>
/*
目的：建立大根堆，也可以变成小根堆，
核心：堆的调整
输入：一系列来自文件的整数。文件中整数以空格隔开
输出：大根堆
*/

void Swap(uint32_t* array, uint32_t i, uint32_t j)
{
	assert(array);
	uint32_t tmp;
	tmp = array[j];
	array[j] = array[i];
	array[i] = tmp;
}

/*大根堆调整*/
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

/*构建大根堆*/
void MaxHeapCreat(uint32_t* array, uint32_t heapSize)
{
	int i;
	for(i = heapSize/2; i >= 0; i--)
	{
		MaxHeapify(array, heapSize, i);
	}
}

/*小根堆调整*/
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
/*构建小根堆*/
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

	/*从文件中读出待排序数据*/
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

    /*构建小根堆并输出*/
    MinHeapCreat(array, heapSize);
    printf("Output the MinHeap:\n");
    for(i = 0; i < heapSize; i++)
    {
        printf("%d\t", array[i]);
    }
    printf("\n");

    /*构建大根堆并输出*/
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
