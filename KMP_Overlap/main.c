#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int findNext(const char *s, int *next)
{
    char s1[100]="$";
    strcat(s1,s);
    int length=strlen(s1);
    //printf("len=%d\n",length);
    //int next[length];
    //next[0]=-1;
    next[1]=0;
    int i=0;
    //int j = next[i];
    for(i=1; i<length-1; i++)
    {
        char a = s1[i+1];
        int v = next[i];
        //compare
        while( (a!=s1[v+1])&&(v>0) )
        {
            v = next[v];
        }
        if( (a)==(s1[v+1]) )
        {
            next[i+1] = v+1;
        }
        else
        {
            next[i+1] = 0;
        }
    }

    //for(i=1;i<=length;i++)
    //{
    //    printf("%d ",next[i]);
    //}
    return 1;
}
int findNext2(const char *s1, int *next)
{
    int length=strlen(s1);
    printf("len=%d\n",length);

    next[0]=-1;
    //next[1]=0;
    int i=0,j=-1;
    //int j = next[i];
    for(i=0; i<length;)
    {
        char a = s1[i];
        //int v = next[i];
        //compare
        if( (-1 == j) || (a==s1[j]) )
        {
            i++,j++;
            next[i] = j;
        }
        else
        {
            j = next[j];
        }
    }
    return 1;
}

int kmp(const char*T, const char*P, char*match)
{
    int n = strlen(T);
    int m = strlen(P);

    int *next =(int*)malloc(strlen(P)*sizeof(int));
    findNext2(P, next);
    int i=1;
    int j=0;
    int index=0;//index for match[]
    while( (i<=m)&&(j<=n) )
    {
        while( (j>0) && (P[i]!=T[j]) )
        {
            j = next[j];
            index = 0;
        }
        if( P[i] == T[j] )
        {
            match[index] = P[i];
            j++;
            i++;
            index++;
        }
        else
        {
            i++;
            index = 0;
        }
        //if use j==n, then is KMP, if use
        //printf("j=%d, i=%d\n",j,i);
        if( (j==n)&&(i<m) )
        {
            printf("has common string, but no overlap\n");
            index=0;
            break;
        }
        else if( i==m )
        {
            printf("get overlap\n");
            break;
        }
    }
    free(next);
    return index;
}
int main()
{
    char *p="ATTATACATTCGATSGATC";
    char *t="ATSGATCDASGACATCAAA";
    int pl = strlen(p);
    int tl = strlen(t);
    printf("P:ATTATACATTCGATSGATC\n");
    printf("T:ATSDASGACATCAAAGATC\n");

    int len = pl<tl?pl:tl;
    char *overlap=(char*)malloc(len*sizeof(char));
    int index = kmp(t, p, overlap);
    printf("Length=%d\n",index);
    int i=0;
    printf("Overlap String:");
    for(i=0;i<index;i++)
    {
        printf("%c",overlap[i]);
    }
    free(overlap);
    //printf("\n%d\n",sizeof(long int));
    return 0;
}
