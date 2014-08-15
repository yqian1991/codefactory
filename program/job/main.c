#include <stdio.h>
#include <stdlib.h>

#define compare(a,b) ((abs(a-b) != (a-b) ? 1 : -1) == 1 ? -1 : ((a-b) == 0 ? 0 : 1))
//A: if a<b  abs(a-b)!= (a-b) ? 1: -1 =   1
//   if a>b  abs(a-b)!= (a-b) ? 1: -1 =   0
//B: if A == 1                -1
//   if A != -1       (a-b) == 0 ? 0 : 1

int main()
{
    compare(1,2);
    printf("%d\n",compare(2,2));
    return 0;
}
