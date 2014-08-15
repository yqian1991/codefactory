#include <stdio.h>
#include <pthread.h>
//静态划分
typedef struct myTestType
{
	int threadID;
	int threadNum;
	int dataNum;

	int *read;
	int *write;
	int *index;
	int *oddNum ;

	pthread_mutex_t  *pMutIndex;
}myTest;

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
	  int index, read, write, oddNum = 0;
	  int threadNum = pMyTest-> threadNum ;
	  int threadID = pMyTest->threadID;
      int dataNum = pMyTest->dataNum;
      //静态划分
      ////划分一次线程处理的数据空间为从firstIndex到lastindex
      //而之间的长度由dataNum/threadNum的大小来划分
      int quotient, firstIndex, lastIndex;
      quotient = dataNum/ threadNum ;
      firstIndex = threadID* quotient ;
      lastIndex = firstIndex + quotient ;
      if(threadID == threadNum -1)
    	  lastIndex = dataNum;
      index = firstIndex ;
      //set finished, start to process
      printf("index=%d.lastIndex=%d.\n",index,lastIndex);
      while(index< lastIndex ){
    	  read = pMyTest->read[index];
    	  write = calculate(read);
		  printf("index=%3u,read=%8u,write=%2u,threadID=%2u \n",index,read,write,threadID);
		  pMyTest->write[index] = write;
		  if(write ==0)
			  oddNum++;
		  index ++;
	}
    printf("****************************\n");
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
		pMyTest->read[i]=i;//指定read的数据
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
	for(i=0;i<threadNum;i++) pthread_join(tid[i],NULL);
	free(tid);
	free(inMyTest);
	pthread_mutex_destroy(pMyTest->pMutIndex);
	free(pMyTest->pMutIndex);
	free(pMyTest->read);
	free(pMyTest->write);
	free(pMyTest->index);
	free(pMyTest-> oddNum);
	free(pMyTest);
	return (0);
}
