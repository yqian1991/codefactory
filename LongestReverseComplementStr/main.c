#include <stdio.h>
#include <string.h>
#include <stdlib.h>
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
    char alphabet[13]=           {'a', 'b','c','d','e','f','g','h','i','j','k','l','m'};
    char alphabet_complement[13]={'n', 'o','p','q','r','s','t','u','v','w','x','y','z'};

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
int main(void)
{//AIBICXYPON
    //char seq1[100]={'A', 'I' ,'B','I', 'C','X','Y','P', 'O','N'};
    char seq1[100]="XXXXMNTGXXXXXXXAIBICXXXXXXPONXXXXXTGAZXXX";
    printf("%s\n", seq1);
    char *seq2;
    seq2=find_complement(seq1);
    printf("%s",seq1);
}
