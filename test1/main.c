#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <stdint.h>

const int MAX = 3;
void Swap(uint32_t* array, uint32_t i, uint32_t j)
{
    assert(array);
    uint32_t tmp;
    tmp = array[j];
    array[j] = array[i];
    array[i] = tmp;
}

void Maxheapify(uint32_t* array, uint32_t heapsize, uint32_t currentnode)
{
    uint32_t leftchild, rightchild, largest;
    leftchild = currentnode * 2 +1;
    rightchild = currentnode * 2 + 2;
    if (leftchild < heapsize && array[leftchild] > array[currentnode])
        largest = leftchild;
    else
        largest = currentnode;
    if (rightchild < heapsize && array[rightchild]>array[largest])
        largest = rightchild;
    if (largest != currentnode){
        Swap(array, largest, currentnode);
        Maxheapify(array, heapsize, largest);
    }

}
void buildMaxheap(uint32_t array,uint32_t heapsize)
{
    int i;
    for(i = heapsize/2; i>=0; i--)
    {
            Maxheapify(array, heapsize, i);
    }
}
int main()
{
    /*int var[3]={10, 20, 30};
    int *ptr[MAX];//指针数组，数组的元素是指向数据的指针
    int (*ptr1)[MAX];//数组指针，ptr1是一个指针，它指向一个数组
    ptr1 = var;

    int i = 0;
    for(i=0; i<MAX; i++){
        ptr[i] = &var[i];
        printf("%d, %d \n", *ptr[i], (*ptr1)[i]);
    }

    double(*p) [3];
    double array[3]={1.0, 2.0, 3.0};
    double a = 1.9;
    double b = 2.1;
    double dd = 3.2;
    //p[0] = &a;
    p=array;
    printf("%0.1f",(*p)[1]);*/

    uint32_t tmp;
    uint32_t *array;
    array = malloc(sizeof(uint32_t));
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
        array = realloc(array, sizeof(uint32_t) * (heapSize ));
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

    /*构建大根堆并输出*/
    buildMaxheap(array, heapSize);
    printf("Output the MaxHeap:\n");
    for(i = 0; i < heapSize; i++)
    {
        printf("%d\t", array[i]);
    }
    free(array);
    fclose(fp);
    return 0;
}
