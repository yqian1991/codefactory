#include<stdio.h>
#include<stdlib.h>
int * reverse(int *a)
{
      int b[5];
      int i=4,j=0;
      for(i=4;i>=0;i--)
      {
          b[j]=a[i];
          printf("b[%d]=%d,",j,b[j]);
          j++;
      }
      printf("\n");
      for(i=0;i<5;i++)
  {
      printf("--r-%d,\n",b[i]);
  }
      return b;
}

int main(){
  int a[5]={1,2,3,4,5};
  int *d=reverse(a);
  //printf("---%d,\n",*(d+1));
  int i=0;
  //int array[5];
  //array=d;
  for(i=0;i<5;i++)
  {
      printf("---%d,\n",d[i]);
  }
}











