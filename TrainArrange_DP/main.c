#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "seqAlign.h"

#define MAX_NUM 100000

void global_align(char *seq1, char *seq2)
{
    printf("Align two sequences\n");
    printf("seq1 length=%d, seq2 length=%d\n", strlen(seq1), strlen(seq2));
}
int main()
{
    FILE *fp;
    fp= fopen("input.txt", "rb");

    char line1[MAX_NUM];
    //char line2[MAX_NUM];
    while(!feof(fp))
    {
        char line1[MAX_NUM];
        char seq1[MAX_NUM];
        char seq2[MAX_NUM];
        //get sequence 1
        fgets(line1, MAX_NUM, fp);
        int len=strlen(line1);
        //printf("%s, %d\n", line1, len);
        int index1=0;
        while(line1[index1]!='\r' && line1[index1]!='\n' && index1<=len)
        {
            //printf("here:%c\n", line1[index1]);
            seq1[index1] = line1[index1];
            index1++;
        }
        printf("seq1=%s,%d\n", seq1, strlen(seq1));
        memset(line1, ' ',strlen(line1));
        //get sequence 2
        fgets(line1, MAX_NUM, fp);
        len=strlen(line1);
        //printf("%s, %d\n", line1, len);
        int index2=0;
        while(line1[index2]!='\r' && line1[index2]!='\n' && index2<=len)
        {
            printf("here:%c\n", line1[index1]);
            seq2[index2] = line1[index2];
            index2++;
        }
        //printf("seq2=%s,%d\n", seq2, strlen(seq2));
        memset(line1, ' ',strlen(line1));

        fgets(line1, MAX_NUM, fp);
        memset(line1, ' ',strlen(line1));

        //global alignment of seq1 and seq2
        global_align(seq1, seq2);
        //int pathsize=strlen(seq1)>strlen(seq2)?strlen(seq1):strlen(seq2);
        //Tpath *path = (Tpath*) malloc(pathsize*sizeof(Tpath));//points in optimal alignment
        //int *pindex;
        //int index=0;
        //pindex=&index;
        //outUsedTime(0);
        //align(seq1, 0, strlen(seq1)-1, seq2, 0, strlen(seq2)-1, path, pindex);
    }
    fclose(fp);
    return 0;
}
