#ifndef SEQALIGN_H_INCLUDED
#define SEQALIGN_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>

#define SEQ_LENGTH 0x10000000
#define LINE_LEN 70           //the number of letters hold in each line

float xprefixy[SEQ_LENGTH];//=(float*) malloc((100)*sizeof(float));
float xsuffixy[SEQ_LENGTH];//=(float*) malloc((100)*sizeof(float));
//store the points on optimal alignment path
typedef struct Tpath//used in traceback
{
    unsigned int seq2i;
    unsigned int seq1j;
}Tpath;

//store two sequences in two txt fiels to two char arrays.
int get2Sequences(char **fname, char *seq1, char *seq2);

//get substring subseq of str, index from start to end
int strCopy(char *str, int start, int end, char *subseq);//used in divide and conguer.

//get the maximun of three float number
float max(float a, float b, float c);//used in get score of each cell, in Dynamic Programming

//reverse a string
char *str_rev(char *str);//used in backward Dynamic Programming

//get the score of substring of x aligned with all the prefix of y
int XAlignPrefixY(char *seq1, int index, char *seq2, float *xprefixy);

//get the score of substring of x aligned with all the suffix of y
int XAlignSuffixY(char *seq1, int index, char *seq2, float *xsuffixy);

//when sequences length <=2 after divide, we align them directly.
int alignShort(char *seq1, int s1, int s2, char *seq2, int s3, int s4, Tpath*path, int *pindex);

//affiliate with qsort(), to sort a struct arrays by a member
int comp( const void *a, const void *b );//used in traceback

int align(char *seq1, int s1, int s2, char *seq2, int s3, int s4, Tpath*path, int *pindex);

//get the optimal alignment between seq1 and seq2, through check path, pindex is the size of path
int traceBack(Tpath *path, int *pindex, char *seq1, char *seq2);

void outUsedTime(int flag);
#endif // SEQALIGN_H_INCLUDED
