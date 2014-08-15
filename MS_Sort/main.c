#include <stdio.h>

//3,2,8,9,1
//5,9,2,1,3,4,6,8,7
#define MAX_NUM 100000
//int start[] = { 5, 1, 4, 3, 2 };
//int target[] = { 3, 1, 2, 5, 4 };
//int target[] = { 1, 2, 3, 4, 5 };
int start[] = {9,8,7,5,4,6,3,2,1,10};
int target[] = {1,2,3,4,5,6,7,8,9,10};
const int length = sizeof(start) / sizeof(*start);

void read_input()
{
    int num[MAX_NUM];
    int i=0;
    FILE *fp;
    fp = fopen("input19.txt","rb");
    if(fp == NULL)
    {
        printf("read file error.\n");
       return 0;
    }

    while (!feof(fp))
	{
		fscanf(fp,"%d",&num[i]);
        i++;
	}
    printf("%d\n",i);
    printf("%d ",num[0]);
    fclose(fp);

    int *array;
    array=num;
    quickSortD(array, 0, i);
}
void dump_canon(int *canon)
{
  int i;
  for (i = 0; i < length; i++)
    printf("%d ", target[canon[i]]);
  printf("\n");
}

int main()
{
  int count=0;
  int i, j, k;
  int canon[length];
  //canon[i] is the index of start[i] in target
  for (i = 0; i < length; i++) {
    for (k = 0; start[i] != target[k]; k++)
      /* NO-OP */
    canon[i] = k;
  }
  printf("Start ");
  dump_canon(canon);
  /* Search for the longest ascending sequence without holes */
  int longest_start;
  int longest_length = 0;
  for (i = 0; i < length; i++) { /* Use i + longest_length < length for optimization */
    k = 1;
    for (j = i + 1; j < length; j++) { /* condition can be optimized */
      if (canon[i] + k == canon[j])
        k++;
    }
    if (k >= longest_length) {
      longest_start = canon[i];
      longest_length = k;
    }
  }
  printf("longest start at:%d with length %d\n",longest_start, longest_length);
  /* Now longest_start has longest_length ordered values */
  /* Increase this ordered values stride by picking a number to put just before or after it */
  while (longest_length < length) {
    for (i = 0; i < length; i++) {
      if (canon[i] + 1 == longest_start) {
        k = canon[i];
        for (j = i; j > 0; j--)
          canon[j] = canon[j - 1];
        canon[0] = k;
        longest_start--;
        longest_length++;
        printf("move %d to the Bottom: ", target[k]);
        count++;
        dump_canon(canon);
      }
      else if (canon[i] == longest_start + longest_length) {
        k = canon[i];
        for (j = i; j < length - 1; j++)
          canon[j] = canon[j + 1];
        canon[length - 1] = k;
        longest_length++;
        /* XXX We just shifted a new value here, redo this index */
        i--;
        printf("move %d to the Top: ", target[k]);
        count++;
        dump_canon(canon);
      }
    }
  }
  printf("Total Moves:%d\n", count);
  read_input();
}
