#ifndef SORT_H_INCLUDED
#define SORT_H_INCLUDED

#define   LENGTH(s)   (sizeof(s)/sizeof(int))
/***********��������*************/
//��������������
void insertSortD(int array[],int n);
//����������������
void insertSortA(int array[],int n);
/***********ѡ������*************/
void selectSortD(int array[],int n);
void selectSortA(int array[],int n);
/***********ð������*************/
void bubbleSortD(int array[],int n);
void bubbleSortA(int array[],int n);
/***********��������*************/
void quickSortD(int array[],int low, int high);
int partition(int array[],int low,int high);
/***********�鲢����*************/
void mergeSort(int array[], int tmpArray[], int left, int right) ;
void merge(int array[],int tmpArray[],int leftPos,int rightPos,int rightEnd);
/***********ϣ������*************/
/************������**************/
//����Ԫ��
void swap(int array[],int i, int j);
//��ӡ����
void print(int array[],int n);
int length(int array[]);
#endif // SORT_H_INCLUDED
