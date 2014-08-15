#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_NUM 60000

int lcsindex[MAX_NUM];
int index_length=0;
char  *lcs;

typedef struct Tpath//used in traceback
{
    unsigned int index;
    unsigned int num;
}Tpath;

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
/*
*Find Longest Common Subsequence
*/
char *lcs_1(char *s, char *t)
{
   char *result;
   int n = strlen(s), m = strlen(t), i, j, **a;

   if (!n || !m) { /* empty input string */
      return "";
   }

   a = (int**)calloc(n + 1, sizeof(int*));
   a[0] = (int*)calloc((n + 1) * (m + 1), sizeof(int));

   for (i = a[0][0] = 0; i <= n; i++) { /* find the length */
      if (!i || (a[i] = a[i - 1] + m)) {
         for (j = 0; j <= m; j++) {
            if (!i || !j) { /* initialize the base row/column */
               a[i][j] = 0;
            } else if (s[i - 1] == t[j - 1]) { /* diagonal step */
               a[i][j] = a[i - 1][j - 1] + 1;
            } else { /* horizontal or vertical step */
               a[i][j] = a[i][j - 1] > a[i - 1][j] ? a[i][j - 1] : a[i - 1][j];
            }
         }
      } else {
         abort(); /* memory failure */
      }
   }
   if (!(i = a[n][m])) {
      return ""; /* no common sub-sequence */
   }

   if (!(result = (char*)malloc(i + 1)) || (result[i] = '\0')) {
      abort(); /* memory allocation failed */
   }
   int flag=i;
   while (n > 0 && m > 0) { /* back track to find the sequence */
      if (s[n - 1] == t[m - 1] && m--) {
         result[--i] = s[--n];
         lcsindex[--flag]=n+1;
      } else {
         a[n][m - 1] >= a[n - 1][m] ? m-- : n--;
      }
   }

   free(a[0]);
   free(a);
   index_length=strlen(result);
    int k=0;
    for(k=0; k<index_length;k++)
    {
        printf("%d ",lcsindex[k]);
    }
    printf("\n");
   return result;
}
/*
*@Name:comp (used by lib function qsort() )
*@Parameter:two cosnt void *
*@Return: int value to declare ascend or descend
*/
int comp( const void *a, const void *b )
{
    Tpath *c= (Tpath *)a;
    Tpath *d= (Tpath *)b;

    if(c->num != d->num)//sort by x value first
        return (*(Tpath *)a).num < (*(Tpath *)b).num ? 1:-1 ;
    else//if x is equal, then sort by y value
        return (*(Tpath *)a).index < (*(Tpath *)b).index ? 1:-1 ;
}

void find_LCIS(Tpath *path, int *pathIndex, int start, int end)
{
    printf("find LCIS...\n");
    int i=start,j=i+1;
    //int length=end-start;
    int pIndex;
    pIndex=*pathIndex;
    while(i<end)
    {
        (path+pIndex)->index=i;
        (path+pIndex)->num=1;
        //printf("find start at:%d,num=%d\n",(path+pIndex)->index,(path+pIndex)->num);
        (*pathIndex)++;pIndex++;

        j=i+1;
        while(lcsindex[i]+j-i==lcsindex[j] &&(j<=end))
        {
          j++;
          (path+pIndex)->index=i;
          (path+pIndex)->num=j-i;
           //printf("find start at:%d,num=%d\n",(path+pIndex)->index,(path+pIndex)->num);
          (*pathIndex)++;pIndex++;
        }
        i++;
    }
}

void tpath_analy(Tpath *path, int *pathIndex, char *copylcs)
{
	//printf("in tpath_analy,LCS:%s\n",lcs);
    FILE *fpout1;
    fpout1=fopen("result.txt","a+");
    printf("in tpath_analy,LCS:\n");
    printf("Find Inverted Repeat...\n");
    int pindex = *pathIndex;
    int i=0;
    for(i=0;i<pindex;i++)
    {
        int start=(path+i)->index;
        int num=(path+i)->num;
        printf("start=%d,num=%d\n",start, num);
        if(lcsindex[index_length-1-start]-lcsindex[index_length-start-num]<=num+1)
        {
            char out[num];
            int rindex=0;
            int a=start;
            for(rindex=0;rindex<num;rindex++)
            {
                out[rindex]=copylcs[a++];
                //printf("%s\n",lcs);
            }
            out[num]='\0';
            printf("%s\n",out);
            fprintf(fpout1, "%s\n", out);
            printf("%d\n",lcsindex[start]);
            fprintf(fpout1, "%d\n", lcsindex[start]);
            printf("%d\n",lcsindex[index_length-1-start-num+1]);
            fprintf(fpout1, "%d\n;\n", lcsindex[index_length-1-start-num+1]);
            break;
        }
    }
    fclose(fpout1);
}

void index_analy( )
{
    //printf("LCS=%s, length:%d\n",lcs, index_length);
    char *copylcs = malloc(index_length*sizeof(char));
    strcpy(copylcs, lcs);
    //printf("LCS=%s, length:%d\n",copylcs, index_length);
    if(index_length==0){
         //printf("LCS=%s, length:%d\n",lcs, index_length);
         printf("Substring Not exist!\n");
         FILE *fpout;
         fpout=fopen("result.txt","a+");
         char ch='-';
         fprintf(fpout, "%c\n;", ch);
         fclose(fpout);
    }
    else{
    	int half_length = index_length/2;
		Tpath *path = (Tpath*) malloc(MAX_NUM*sizeof(Tpath));
		int a=0;
		int *pathIndex=&a;
		printf("pIndex:%d\n",*pathIndex);
		//*pathIndex=a;

		//printf("LCS=%s, length:%d\n",copylcs, index_length);
		find_LCIS(path,pathIndex, 0, half_length-1);
		find_LCIS(path,pathIndex, half_length, index_length-1);
		printf("Tpath size:%d\n", *pathIndex);

		qsort(path, *pathIndex, sizeof(path[0]), comp);//sort the points first
		//printf("start at:%d,num=%d\n",(path+1)->index,(path+1)->num);
		tpath_analy(path, pathIndex, copylcs);
    }
    free(copylcs);
}

int main() {
    //char seq1[100]="XXXXMNTGXXXXXXXAIBIXXXXXXONXXXXXTXGXAXZXXX";
    //char seq1[100]="AIBICXYPON";
	FILE *fp;
    fp= fopen("input22.txt", "rb");

    char line1[MAX_NUM];

    while(!feof(fp))
    {
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

        char seqcopy[MAX_NUM];
        strcpy(seqcopy, seq1);

        char *seq2;
        seq2=find_complement(seqcopy);

        lcs=lcs_1(seq1,seq2);
	    printf("LCS:%s\n", lcs);
	    printf("%d\n", strlen(lcs));

	    index_analy( );

	    printf("finished!\n");
	    memset(lcsindex, ' ', index_length);
	    memset(lcs, ' ', index_length);
	    index_length=0;
    }
	return 0;
}

