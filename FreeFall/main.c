#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE *fp;
    fp= fopen("C://Users//Administrator//Downloads//input22.txt", "rb");
    //fp= fopen("input23.txt", "rb");

    char line1[MAX_NUM];
    //char line2[MAX_NUM];
    while(!feof(fp))
    {
        //char line1[MAX_NUM];
        char seq1[MAX_NUM];
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
        printf("******start**************\n");
        printf("Input sequence length=%d\n",strlen(seq1));
        memset(line1, ' ',strlen(line1));
        //get sequence 2 :';'
        fgets(line1, MAX_NUM, fp);
        memset(line1, ' ',strlen(line1));



	    printf("finished!\n");
    }
	return 0;
    return 0;
}
