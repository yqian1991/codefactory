/*
 * seqAlign.c
 *
 *  Created on: Oct 8, 2013
 *      Author: yqian33
 */

#include <stdio.h>
#include <stdlib.h>
#include "seqAlign.h"


/*
*@Name: get2Sequences
*@Parameter: strings that accept sequences
*@Return: 1 if succeed, 0 vise versa
*/
int get2Sequences(char **fname, char *seq1, char *seq2)
{
    char ch;//get char in file one by one.
    char *buff = (char*) malloc(SEQ_LENGTH*sizeof(char));
    if(buff==NULL){
        printf("malloc failed!\n");
        return 0;
    }

    int i=0;
    FILE *fp=NULL;
    for (i=0;i<2;i++)
    {
        fp = fopen(fname[i],"r");
        if( fp==NULL )
        {
            printf("open file error\n");
            return 0;
        }
        int j=0;
        while( (ch=fgetc(fp)) != EOF )
        {
            //printf("ch=%c\n",ch);
            if(ch!='\n')
            {
	      // ch = ' ';
              buff[j]=ch;j++;
            }
	    // buff[j]=ch;
            //j++;
        }
        //printf("ok\n");
        if(i==0){//judge to store which sequences
            //seq1=(char*) malloc(j*sizeof(char));
            strcpy(seq1,buff);
            //printf("seq1=%s\n",seq1);
        }
        if ( i==1 ){
            //seq2=(char*) malloc(j*sizeof(char));
            strcpy(seq2,buff);
            //printf("seq2=%s\n",seq2 );
        }
        memset(buff,0,SEQ_LENGTH*sizeof(char));
        fclose(fp);
    }
    printf("Now you have two Sequences in memory\n");
    free(buff);
    return 1;
}

/*
*@Name:strCopy
*@Parameter: a string and start, end index
*@Return: subseq of str,index from start to index
*/
int strCopy(char *str, int start, int end, char *subseq)
{
    //char result[end-start+1];
    int i=0;
    for(i=start; i<=end; i++)
    {
        subseq[i-start] = str[i];
        //printf("%c\n",result[i-start]);
    }
   // printf("over");
    return 1;
}

/*
*@Name:max
*@Parameter:a,b,c (all of them are float numbers)
*@Return: the maxmium value among input a,b,c
*/
float max(float a, float b, float c)
{
    float max = a;
    if( b>max )
    {
        max = b;
    }
    if( c>max )
    {
        max = c;
    }
    return max;
}

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

/*
*@Name:XAlignPrefixY
*@Parameter:seq1 with its index, seq2 and xprefixy to store the results
*@Return: 1 ok, 0 error.
*/
int XAlignPrefixY(char *seq1, int index, char *seq2, float *xprefixy)
{
    int m=index;
    int n=strlen(seq2);
    //printf("seq1 len(index)=%d,seq2 len(n)=%d\n", m,strlen(seq2));

    float match = 1;
    float mismatch = -1;
    float indel = -1;//define score schema

    xprefixy[0] = index*indel;

    float score[strlen(seq1)+strlen(seq2)];//linear space to store scores
    float bestScore=-100;//update to get the bestScore
    float temp = 0.0;//co-op with score[] to calculate score of every cell

    int i=0,j=0;
    for(i=0;i<=m;i++)//record the score of first row
    {
        score[i] = 0+i*indel;
        //printf("%0.1f ",score[i]);
    }
    //printf("\n");

    for(j=1;j<=n;j++)
    {
        for(i=0;i<=m;i++)
        {
            if(i==0)//score of first column
            {
                temp = score[i];
                score[i]=j*indel;
                //printf("%0.1f ",score[i]);
            }else
            {
                float matchor = seq2[j-1]==seq1[i-1]?match:mismatch;
                //printf("matchor=%f \n",matchor);
                float cur_score = max(score[i]+indel, score[i-1]+indel, temp+matchor);
                temp = score[i];//save score[i] to used in the next cell.
                score[i]=cur_score;
                //printf("%0.1f ",cur_score);
                bestScore = cur_score;
            }
        }
        xprefixy[j] = bestScore;
        //printf(" xprefixy[%d]:%f\n",j,xprefixy[j] );//what we need to use in later alignment
    }
    //printf("-------above are matrix x align prefix of y------\n");
    //printf("-------------------------------------------------\n");
    return 1;
}

/*
*@Name:XAlignSuffixY
*@Parameter:seq1 with its index, seq2 and xsufixy to store the results
*@Return: 1 ok, 0 error.
*/
int XAlignSuffixY(char *seq1, int index, char *seq2, float *xsuffixy)
{
    int n_index = strlen(seq1) - index+1;
    //int n = strlen(seq2);
    //float xsuffixy[n+1];

    char tmp1[strlen(seq1)];
    tmp1[strlen(seq1)]='\0';

    char tmp2[strlen(seq2)];
    tmp2[strlen(seq2)]='\0';

    memcpy(tmp1, seq1,sizeof(tmp1));//we don't want seq1 and seq2 reversed really
    memcpy(tmp2, seq2,sizeof(tmp2));

    //use XAlignPrefixY to execute backward dynamic programming
    XAlignPrefixY(str_rev(tmp1), n_index, str_rev(tmp2), xsuffixy);

    return 1;
}

/*
*@Name:alignShort(when sequences length <2, we can align them directly)
*@Parameter:seq1 with its index, seq2 with index and path to receive points
*@Parameter:s1, s2, s3, s4 only used to calculate the final x,y value in matrix
*@Return: 1 ok, 0 error.
*/
int alignShort(char *seq1, int s1, int s2, char *seq2, int s3, int s4, Tpath*path, int *pindex)
{
	//printf("in alignshort():seq1:%s\n",seq1);
	//printf("in alignshort():seq2:%s\n",seq2);
    //score first
    int n=strlen(seq1);
    int m=strlen(seq2);
    float score[m+1][n+1];//score matrix

    float match = 1;
    float notmatch = -1;
    float indel = -1;//scoring schema, maybe can define in head files as a struct


    int i = 0,j=0;
    score[0][0]=0.0;//initial the first gap-gap cell
    for(i=1;i<=n;i++)
    {
        score[0][i] = indel * i;
        //printf("%0.2f,",score[0][i]);
    }
    //printf("\n");
    for(i=1;i<=m;i++)
    {
        score[i][0] = indel*i;
        //float s=score[i][0];
        //printf("%0.2f,",s);
    }
    //printf("\n");
    for(i=1;i<=m;i++)
    {
        for(j=1;j<=n;j++)
        {
            float matchor = (seq2[i-1] == seq1[j-1]?match:notmatch);
            score[i][j] = max(score[i-1][j]+indel, score[i][j-1]+indel, score[i-1][j-1]+matchor);
            //printf("%0.2f ",score[i][j]);
        }
        //printf("\n");
    }
    //as we find the score mataix use above code

    //then we trace back to find point
    i=m,j=n;//i is the index of seq2, j is the index of seq1
    //printf("j=%d,n=%d,m=%d\n",j,n,m);
    int a=0;//index the path pointer
    while( (i>0)||(j>0) )
    {
        if(score[i][j]==(score[i][j-1]+indel))//gap
        {
            //record i, j-1 to path
            a=*pindex;
            //printf("a=%d\n",a);
            (path+a)->seq2i = i+s3;
            (path+a)->seq1j = j-1+s1;
            (*pindex)++;
            //printf("test(%d,%d)\n", i-1 , j-1);
            j--;

        }
        else if(score[i][j]==(score[i-1][j]+indel))//gap
        {
            //record i-1, j to path
            a=*pindex;
            //printf("a=%d\n",a);
            (path+a)->seq2i = i-1+s3;
            (path+a)->seq1j = j+s1;
            (*pindex)++;
            //printf("test(%d,%d)\n",  i-1 ,j-1);
            i--;
        }
        else//match or mismatch from dignoal cell
        {
            //record i-1, j-1 to path
            a=*pindex;
            (path+a)->seq2i = i-1+s3 ;
            (path+a)->seq1j = j-1+s1 ;
            (*pindex) ++;
            //printf("test(%d,%d)\n", i-1 ,j-1);
            i--;
            j--;
        }
    }
    return 0;
}

/*
*@Name:align(use divide and conquer strategy and linear space)
*@Parameter:seq1 with its index, seq2 with index and path to receive points
*@Parameter:s1, s2, s3, s4 only used to calculate the final x,y value in matrix
*@Return: 1 ok, 0 error.
*/
int align(char *seq1, int s1, int s2, char *seq2, int s3, int s4, Tpath*path, int *pindex)
{

    //printf("align:%s and %s\n",seq1, seq2);
    int n = strlen(seq1);
    //printf("n=%d\n",n);
    int number = strlen(seq2);
    //printf("seq1 size=%d,seq2 size=%d\n",n,number);

    if( (n<=2)||(number<=2) )
    {
        //printf("n<2 or number < 2, execute alignShort()\n");
        alignShort(seq1, s1, s2, seq2, s3, s4, path, pindex);
    }else
    {
        //float *xprefixy=(float*) malloc((number+1)*sizeof(float));
        //float *xsuffixy=(float*) malloc((number+1)*sizeof(float));

        float bestCost=-100.0;
        int bestq=0;//the point we conduct divide and conquer

        //get the alignment score with prefix and suffix of y, with half of x
        if(!XAlignPrefixY(seq1, n/2, seq2, xprefixy))
        {
            printf("XAlignPrefixY wrong!!!\n");
            return 0;
        }
        if(!XAlignSuffixY(seq1, n/2+1, seq2, xsuffixy))
        {
            printf("XAlignSuffixY wrong!!!\n");
            return 0;
        }
        //print the score to test
        /*int k=0;
        for(k=0;k<=number;k++)
        {
                printf("prefix:%0.2f ",xprefixy[k]);
                printf("suffix:%0.2f\n",xsuffixy[k]);
        }*/

        //to get the point to conduct divide and conquer
        int q=0;
        for(q=0;q<=number;q++)
        {
            float cost = xprefixy[q]+xsuffixy[number-q];
            //printf("cost=%f, prefix=%f,%f\n", cost, xprefixy[q], xsuffixy[number-q]);
            if( cost>=bestCost )
            {
                bestCost = cost;
                bestq = q;//no need to record (bestq, n/2)
            }
        }
        //printf("now bestq is %d, best score is %f.\n",bestq,bestCost);

        //divide the sequence to two half
        //char xseq_1[n/2];//from x , 0-n/2-1
        char *xseq_1 = (char*) malloc((n)*sizeof(char));
        //char yseq_1[bestq];//from y, from 0, bestq-1;
        char *yseq_1 = (char*) malloc((number)*sizeof(char));
        //char xseq_2[n-n/2];//from x, from  n/2 to n-1
        char *xseq_2 = (char*) malloc((n)*sizeof(char));
        //char yseq_2[number-bestq];//from y, from bestq, m-1;
        char *yseq_2 = (char*) malloc((number)*sizeof(char));

        if(bestq>0)
        {
            strCopy(seq1, 0, n/2-1, xseq_1);//???????????????????????????????
            xseq_1[n/2]='\0';//??????????????????????????????????????????????
            //printf("xseq_1: %s\n",xseq_1);//problem on Linux, ???????????????

            strCopy(seq1, n/2, n-1, xseq_2);
            xseq_2[n-n/2]='\0';
            //printf("xseq_2: %s\n",xseq_2);

            strCopy(seq2,0,bestq-1,yseq_1);
            yseq_1[bestq]='\0';
            //printf("yseq_1: %s\n",yseq_1);

            strCopy(seq2,bestq,number-1,yseq_2);
            yseq_2[number-bestq]='\0';
            //printf("yseq_2: %s\n",yseq_2);

            align(xseq_1, s1, s1+n/2-1, yseq_1, s3, s3+bestq-1, path, pindex);
            align(xseq_2, s1+n/2, s2,yseq_2, s3+bestq, s4, path, pindex);
        }else
        {
            strCopy(seq1, 0, n/2-1, xseq_1);//???????????????????????????????
            xseq_1[n/2]='\0';//??????????????????????????????????????????????
            //printf("xseq_1: %s\n",xseq_1);//problem on Linux, ???????????????

            strCopy(seq1, n/2, n-1, xseq_2);
            xseq_2[n-n/2]='\0';
           // printf("xseq_2: %s\n",xseq_2);

            strcpy(yseq_1, "");
            strcpy(yseq_2,seq2);

            align(xseq_1, s1, s1+n/2-1, yseq_1, s3, s3, path, pindex);
            align(xseq_2, s1+n/2, s2,yseq_2, s3+bestq, s4, path, pindex);
        }

        //free(xseq_1);
        //free(yseq_1);
        //free(xseq_2);
        //free(yseq_2);
    }

    return 1;
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

    if(c->seq2i != d->seq2i)//sort by x value first
        return (*(Tpath *)a).seq2i > (*(Tpath *)b).seq2i ? 1:-1 ;
    else//if x is equal, then sort by y value
        return (*(Tpath *)a).seq1j > (*(Tpath *)b).seq1j ? 1:-1 ;
}

/*
*@Name:traceBack
*@Parameter:Tpath, int *, char *, char *
*@Parameter:Tpath store the points in optimal alignments, two seqs is the original sequences
*@Return: 1 ok, 0 false
*/
int traceBack(Tpath *path, int *pindex, char *seq1, char *seq2)
{
    int number = *pindex;//assign the value of path size
    //printf("number=%d,size=%d,sort first\n",number, sizeof(path[0]));

    qsort(path, number, sizeof(path[0]), comp);//sort the points first

    //add the last node, as last node didn't store in path before when doing alignment
    (path+number)->seq2i = strlen(seq2);
    (path+number)->seq1j = strlen(seq1);
    (*pindex)++;
    number++;
    printf("Total path size=%d\n",*pindex);

    //int l=0;
    //for (l=0;l<number;l++)
    //{
    //    printf("(%d,%d)\n",(path+l)->seq2i,(path+l)->seq1j);
    //}

    //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    //char align_seq1[1000];//care of the memory
    //char align_seq2[1000];//!!!!!!!!!!!!!!!!!!!
    //char alignMark[1000];//!!!!!!!!!!!!!!!!!!!
    //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    char *align_seq1=(char*)malloc(SEQ_LENGTH*sizeof(char));
    char *align_seq2=(char*)malloc(SEQ_LENGTH*sizeof(char));
    char *alignMark=(char*)malloc(SEQ_LENGTH*sizeof(char));

    float score=0;//record the final score of optimal alignment
    int k=0, i=0;
    for(k=number-1;k>0;k--)
    {
        //printf("k=%d\n",k);
        int cur_x=(path+k)->seq2i;
        int prev_x=(path+k-1)->seq2i;

        int cur_y=(path+k)->seq1j;
        int prev_y=(path+k-1)->seq1j;

        //printf("(%d,%d) (%d,%d)\n",cur_x,cur_y,prev_x,prev_y);
        //((path+k)->seq2i = (path+k-1)->seq2i) and ((path+k)->seq1j =1 + (path+k-1)->seq1j) then a gap in seq2
        if( (cur_x == prev_x)&&(cur_y == prev_y+1) )//a gap in seq2
        {
            score--;
            align_seq1[i] = seq1[cur_y-1];
            align_seq2[i] = '-';
            alignMark[i]=' ';
            //printf("-%c-\n",align_seq1[i]);
            //printf("-%c-\n",align_seq2[i]);
            i++;
        }

        //(path+k)->seq1j = (path+k-1)->seq1j and ((path+k)->seq2i =1 + (path+k-1)->seq2i)then a gap in seq2
        else if( (cur_y == prev_y)&&(cur_x == 1 + prev_x) )// a gap in seq1
        {
            score--;
            align_seq2[i] = seq2[cur_x-1];
            align_seq1[i] = '-';
            //printf("-%c-\n",align_seq1[i]);
            //printf("-%c-\n",align_seq2[i]);
            alignMark[i]=' ';
            i++;
        }
        else{//match or mismatch
            //printf("no gap\n");
            align_seq1[i] = seq1[cur_y-1];
            align_seq2[i] = seq2[cur_x-1];
            //printf("-%c-\n",align_seq1[i]);
            //printf("-%c-\n",align_seq2[i]);
            //printf("no gap\n");
            if (seq1[cur_y-1] == seq2[cur_x-1])//match
            {
                score++;
                alignMark[i]='*';
            }
            else//mismatch
            {
                score--;
                alignMark[i]=' ';
            }
            i++;
        }
    }//end trace back cycle

    //-------------------------------------------------
    //*************now write alignment to file*********
    //-------------------------------------------------

    align_seq1[i]='\0';
    align_seq2[i]='\0';
    alignMark[i]='\0';
    //printf("now i=%d\n",i);
    //printf("%s\n",align_seq1);
    //printf("%s\n",(align_seq2));
    //printf("%s\n",(alignMark));

    //reverse sequences first.
    //printf("before str_rev:%s\n",align_seq1);
    str_rev(align_seq1);
    //printf("after str_rev:%s\n",align_seq1);

    //printf("before str_rev:%s\n",align_seq2);
    str_rev(align_seq2);
    //printf("after str_rev:%s\n",align_seq2);

    str_rev(alignMark);

    printf("-----write alignment to file...\n");
    FILE *fp = fopen("align_result.txt","w");
    if(fp==NULL)
    {
        printf("open align_result.txt file error\n");
        return 0;
    }
    int u=0;
    i=strlen(align_seq1);// now i is the number of chars we need to write to file
    //printf("strlen i=%d",i);
    //printf("out ok,%d, %s\n",strlen(sub1),sub1);
    while(u*LINE_LEN<i)
    {
        //printf("ok u=%d\n",u);
        //char s2[LENGTH];
        //char s3[LENGTH];
        int m=0;
        if((i-LINE_LEN*u)<LINE_LEN)
        {
            for(m=LINE_LEN*u;m<i;m++)
            {
                fwrite(&align_seq1[m],1,1,fp);
            }
            fwrite("\n",1,1,fp);

            for(m=LINE_LEN*u;m<i;m++)
            {
                fwrite(&align_seq2[m],1,1,fp);
            }
            fwrite("\n",1,1,fp);

            for(m=LINE_LEN*u;m<i;m++)
            {
                fwrite(&alignMark[m],1,1,fp);
            }
            fwrite("\n",1,1,fp);
        }else
        {
            for(m=LINE_LEN*u;m<LINE_LEN*(u+1);m++)
            {
                fwrite(&align_seq1[m],1,1,fp);
            }
            fwrite("\n",1,1,fp);

            for(m=LINE_LEN*u;m<LINE_LEN*(u+1);m++)
            {
                fwrite(&align_seq2[m],1,1,fp);
            }
            fwrite("\n",1,1,fp);

            for(m=LINE_LEN*u;m<LINE_LEN*(u+1);m++)
            {
                fwrite(&alignMark[m],1,1,fp);
            }
            fwrite("\n",1,1,fp);
        }
        fwrite("\n",1,1,fp);
        u++;
    }
    fclose(fp);

    //printf("final score is:%0.2f\n",score);

    free(align_seq1);
    free(align_seq2);
    free(alignMark);
    return 1;
}

/*
 * calculate the time consuming of this program
 */
void outUsedTime(int flag)
{
	static struct timeval tp_start, tp_end;//struct defined in time.h, used to save the accurate system time
	double time_used;
	static unsigned long start_cpu, end_cpu; // CPU time

	if (flag == 0) {
		gettimeofday(&tp_start, NULL);
		//set start time: CPU time
		start_cpu = clock();
	} else {
		//set end time: CPU time
		end_cpu = clock();
		//print the system time
		gettimeofday(&tp_end, NULL);
		//print the CPU time
		printf("Total CPU time used: %.2f seconds.\n", (double) (end_cpu- start_cpu) / CLOCKS_PER_SEC);
		time_used = (1000000 * (tp_end.tv_sec - tp_start.tv_sec)
				+ (double) (tp_end.tv_usec - tp_start.tv_usec)) / 1000000;
		printf("Total Used Time By gettimeofday(): %.2f Seconds.\n", time_used);
		gettimeofday(&tp_start, NULL);
		//设置开始时�? CPU time
		start_cpu = clock();
	}
	return;
}
