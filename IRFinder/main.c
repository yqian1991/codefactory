#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_NUM 60000

/*
*@Name:str_rev
*@Parameter:str that need to reverse
*@Return: str that has been reversed
*/
char *str_rev(char *str)
{
      char *p1, *p2;

      if (! str || ! *str)
            return str;
      for (p1 = str, p2 = str + strlen(str) - 1; p2 > p1; ++p1, --p2)
      {
            *p1 ^= *p2;
            *p2 ^= *p1;
            *p1 ^= *p2;
      }
      return str;
}

char* find_complement(char *seq)
{
    //char alphabet[13]=           {'a', 'b','c','d','e','f','g','h','i','j','k','l','m'};
    //char alphabet_complement[13]={'n', 'o','p','q','r','s','t','u','v','w','x','y','z'};

    int length = strlen(seq);
    char *seq2=str_rev(seq);
    //printf("%s, length=%d\n",seq2, strlen(seq2));

    int i=0;
    for(i=0; i<length; i++)
    {
        if(seq2[i]>='A' && seq2[i] <='M')
        {
            seq2[i]+=13;
        }
        else if(seq2[i]>='N' && seq2[i] <='Z')
        {
           seq2[i]-=13;
        }
    }
    //printf("%s, length=%d\n",seq2, strlen(seq2));
    return seq2;
}



typedef struct Tpath//used in traceback
{
	unsigned int count;
    unsigned int start;
    unsigned int irstart;
    char flag;
}Tpath;

Tpath *path;

int irequal(char a, char b)
{
	int flag=0;
	if( (a-b==13) ||(b-a)==13 )
	{
		flag = 1;
	}else
	{
		flag = 0;
	}
	return flag;
	//return ( (a-b=13) || (b-a)==13 )?1:0;
}
Tpath* checkFromLeftSide(char *seq, int i, int j)
{
    //printf("check from left(%d, %d)...\n", i, j);
    int count = 1;
    int gap = 0;
    char mark[MAX_NUM];
    int mindex=0;

    int tempi = i;//
    int tempj = j;
    //printf("lj:%d,%d\n", i,j);
    while( i<j )
    {
        if( irequal(seq[i], seq[j]))
        {
            //printf("here\n");
            count++;
            i++;j--;
            mark[mindex++]='M';

        }
        else
        {
            j--;
            gap++;
            mark[mindex++]='G';
        }
        if(gap>2)
        {
            //printf("gap=2\n");
            break;
        }
    }
    mark[mindex]='\0';
    //printf("mindex=%d, %s, %c %c\n", mindex,mark, mark[mindex-1], mark[mindex-2]);
    //count, tempi-1(start), j
    Tpath *path1=(Tpath*)malloc(sizeof(Tpath));
    path1->count=count;
    path1->start=tempi-1;
    if(mark[mindex-1]=='M')
    {
        path1->irstart=tempj-mindex+1;
    }
    else if(mark[mindex-1]=='G' && mark[mindex-2]=='M')
    {
        path1->irstart=tempj-mindex+2;
    }
    else if(mark[mindex-1]=='G' && mark[mindex-2]=='G' && mark[mindex-3]=='M')
    {
        path1->irstart=tempj-mindex+3;
    }
    else if(mark[mindex-1]=='G' && mark[mindex-2]=='G'&& mark[mindex-3]=='G')
    {
        path1->irstart=tempj-mindex+4;
    }
    path1->flag='L';
    //printf("result %d,%d,%d, L\n", count, tempi-1, j+2);
    return path1;
}

Tpath* checkFromRightSide(char *seq, int i, int j)
{
    //printf("check from right...\n");
    int count = 1;
    int gap = 0;

    int tempi = i;
    //int tempj = j;
    while( i<j )
    {
        if( irequal(seq[i], seq[j]))
        {
            count++;
            i++;j--;
        }
        else
        {
            i++;
            gap++;
        }
        if(gap>2)
        {
            break;
        }
    }

    //count, tempi-1, j(start)
    Tpath *path1 = (Tpath*)malloc(sizeof(Tpath));
    path1->count=count;
    path1->start=j+1;
    path1->irstart=tempi-1;
    path1->flag='R';
    //printf("result %d,%d,%d, R\n", count, j+1, tempi-1);
    return path1;
}

void checkI2J(char *seq, int i, int j)
{
    //printf("check %d to %d\n", i, j);
	if( irequal(seq[i], seq[j]) )
	{
	    //printf("go on checking...\n");
	    Tpath *pathL = (Tpath*)malloc(sizeof(Tpath));
	    Tpath *pathR = (Tpath*)malloc(sizeof(Tpath));
	    Tpath *pathTemp = (Tpath*)malloc(sizeof(Tpath));

        pathL = checkFromLeftSide(seq, i+1, j-1);
        pathR = checkFromRightSide(seq, i+1, j-1);
        //printf("pathL:%d, %d, %d, %c\n", pathL->count, pathL->start, pathL->irstart, pathL->flag);
        //printf("pathR:%d, %d, %d, %c\n", pathR->count, pathR->start, pathR->irstart, pathR->flag);

        pathTemp = ( (pathL->count)>=(pathR->count)?pathL:pathR );
        //printf("pathTemp:%d, %d, %d, %c\n", pathTemp->count, pathTemp->start, pathTemp->irstart, pathTemp->flag);

        if(pathTemp->count >= path->count)
        {
            path = pathTemp;
        }

	}
    //printf("checkI2J:%d, %d, %d, %c\n", path->count, path->start, path->irstart, path->flag);
}

void findIR(char *seq1)
{
    printf("findIR...\n\n");
    FILE *fpout;
    fpout= fopen("result.txt", "a");
	int length = strlen(seq1);
	int i=0,j=0;
	for(i=0; i<length-1; i++)
	{
		for(j=i+1; j<length; j++)
		{
			checkI2J(seq1, i, j);
		}
	}
	printf("Result:%d, %d, %d, %c\n", path->count, path->start, path->irstart, path->flag);

	char str[path->count+1];
	int index=0;
	int start=path->start;

    if( path->count > 0)
    {
        while(index < path->count)
        {
            str[index++]=seq1[start++];
        }
        str[path->count]='\0';
        printf("%c\n", str[path->count]);
        fprintf(fpout, "%s\n", str);
        fprintf(fpout, "%d\n", path->start+1);
        fprintf(fpout, "%d\n;\n", path->irstart+1);
    }
    else if( path->count ==0 )
    {
        char ch='-';
        fprintf(fpout, "%c\n;\n", ch);
    }
    fclose(fpout);
}

int main() {
    //char seq1[100]="XXXXMNTGXXXXXXXAIBIXXXXXXONXXXXXTXGXAXZXXX";
    //char seq1[100]="AIBICXYPON";

	FILE *fp;
    fp= fopen("C://Users//Administrator//Downloads//input21.txt", "rb");
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

        path = (Tpath*)malloc(sizeof(Tpath));
        path->count=0;
        path->start=0;
        path->irstart=0;
        path->flag='T';

        findIR(seq1);

	    printf("finished!\n");
    }
	return 0;
}

