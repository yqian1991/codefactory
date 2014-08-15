#ifndef SORT_H_INCLUDED
#define SORT_H_INCLUDED

#define   LENGTH(s)   (sizeof(s)/sizeof(int))
/***********≤Â»Î≈≈–Ú*************/
//≤Â»Î≈≈–ÚΩµ–Ú≈≈¡–
void insertSortD(int array[],int n);
//≤Â»Î≈≈–Ú…˝–Ú≈≈¡–
void insertSortA(int array[],int n);
/***********—°‘Ò≈≈–Ú*************/
void selectSortD(int array[],int n);
void selectSortA(int array[],int n);
/***********√∞≈›≈≈–Ú*************/
void bubbleSortD(int array[],int n);
void bubbleSortA(int array[],int n);
/***********øÏÀŸ≈≈–Ú*************/
void quickSortD(int array[],int low, int high);
int partition(int array[],int low,int high);
/***********πÈ≤¢≈≈–Ú*************/
void mergeSort(int array[], int tmpArray[], int left, int right) ;
void merge(int array[],int tmpArray[],int leftPos,int rightPos,int rightEnd);
/***********œ£∂˚≈≈–Ú*************/
/************∂—≈≈–Ú**************/
//Ωªªª‘™Àÿ
void swap(int array[],int i, int j);
//¥Ú”° ˝◊È
void print(int array[],int n);
int length(int array[]);
#endif // SORT_H_INCLUDED
