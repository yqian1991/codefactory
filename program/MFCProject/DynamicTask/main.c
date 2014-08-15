#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
//动态任务划分
typedef struct myTestType
{
	int threadID;
	int threadNum;
	int dataNum;

	int *read;
	int *write;
	int *index;
    int* oddNum;
	pthread_mutex_t  *pMutIndex;
}myTest;

#define STEP_SIZE  10

int oddIndex(int composite, myTest* pMyTest) {
	int i, odd, dataNum,maxOdd,index ;
     index=-1; maxOdd=0;
     dataNum = pMyTest-> dataNum ;

	for(i=0;i< dataNum ;i++){
	     if((pMyTest ->write[i] ==0)&&(composite %pMyTest ->read[i] == 0))
	     {
	         if(pMyTest ->read[i] > maxOdd){
                     maxOdd  = pMyTest ->read[i] ;
                     index = i;
	         }
	     }
	}

	return index;
}

int calculate(int read) {
	int write = 0; //奇数：0，其他：1
    if(read%2 == 0){
        write = 1;
	}
	if(write==0)
		Sleep(1);
	return write;
}

void thread(myTest* pMyTest) {
	//printf("Begin threadID = %u Run!\n",pMyTest->threadID);
	int index, read, write, i, oddNum = 0;
	int threadID = pMyTest->threadID;
	int dataNum = pMyTest->dataNum;
    int nextIndex, stepSize = STEP_SIZE;
	pthread_mutex_lock(pMyTest->pMutIndex);
	index = pMyTest->index[0];  //pMyTest->index[0]++;
	pMyTest->index[0]+= stepSize ;
	pthread_mutex_unlock(pMyTest->pMutIndex);
	while(index<dataNum){
		read = pMyTest->read[index];
		//动态任务划分，设置步长变量
		nextIndex = (index+stepSize<dataNum)?(index+stepSize ):dataNum;
		printf("index=%3u,nextIndex=%3u.\n",index,nextIndex) ;
		for(i=index; i<nextIndex; ++i ) {
			write = calculate(read);
		    printf("index=%3u,read=%8u,write=%2u,threadID=%2u \n",i,read,write,threadID);
		    pMyTest->write[i] = write;
		    read = pMyTest->read[i];//重新设置待判断数
	    }
		pthread_mutex_lock(pMyTest->pMutIndex);
		index = pMyTest->index[0];  //pMyTest->index[0]++;
		pMyTest->index[0]+= stepSize ;
		pthread_mutex_unlock(pMyTest->pMutIndex);
		if(write ==0)
			oddNum++;
		printf("**********************\n");
	}
	pthread_mutex_lock(pMyTest->pMutIndex);
    pMyTest-> oddNum[0] += oddNum;
	pthread_mutex_unlock(pMyTest->pMutIndex);
	pthread_exit(NULL);
}

int main(void) {
	int i,ret;
	int threadNum = 2;
	myTest* pMyTest = (myTest*) malloc(sizeof(myTest));
	pMyTest->dataNum =  20;
	pMyTest->read = (int*) malloc(sizeof(int)*pMyTest->dataNum);
	pMyTest->write = (int*) malloc(sizeof(int)*pMyTest->dataNum);
	for(i=0;i<pMyTest->dataNum;++i){
		//if(i%4==0)
			//pMyTest->read[i]=(1<<(i%30))+1;
		//else
		//{
			//pMyTest->read[i]=(7<<(i%16))+1;
		//}
		pMyTest->read[i]=i;//read赋值
	}
	pMyTest->index = (int*) calloc(1,sizeof(int));

	pMyTest->pMutIndex = (pthread_mutex_t*) malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(pMyTest->pMutIndex, NULL);

	pMyTest->threadNum = threadNum;
	myTest* inMyTest = (myTest*) malloc(sizeof(myTest)*threadNum);
	for(i=0;i<threadNum;++i)
	{
		memcpy(inMyTest+i,pMyTest,sizeof(myTest));
		(inMyTest+i)->threadID = i;
	}
	pthread_t *tid = (pthread_t*) malloc(sizeof(pthread_t)*threadNum);
	printf ("Begin create pthread!\n");
	for(i=0;i<threadNum;++i){
		ret = pthread_create(tid+i, NULL,(void*)thread,(myTest*)(inMyTest+i));
		if(ret!=0){
			printf ("Create pthread error!\n");
			return 0;
		}
	}
	for(i=0;i<threadNum;i++)
		pthread_join(tid[i],NULL);

	free(tid);
	free(inMyTest);
	pthread_mutex_destroy(pMyTest->pMutIndex);
	free(pMyTest->pMutIndex);
	free(pMyTest->read);
	free(pMyTest->write);
	free(pMyTest-> oddNum);
	free(pMyTest->index);
	free(pMyTest);
	return (0);
}
