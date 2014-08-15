#include <iostream>
#include <windows.h>
#include <time.h>
#include "cycle.h"

using namespace std;

int main()
{
    DWORD start_time=GetTickCount();
    clock_t cstart_time=clock();

    ListNode *node1=new ListNode(3);
    ListNode *node2=new ListNode(2);
    ListNode *node3=new ListNode(0);
    ListNode *node4=new ListNode(-4);
    node1->next=node2;
    node2->next=node3;
    node3->next=node4;
    node4->next=node2;

    Solution sol;// = new Solution();
    sol.detectCycle(node1);

    int a[200][200];
    int i,j;

    for(i=0; i<200; i++)
    {
        for(j=0; j<200; j++)
        {
            a[i][j]=1;
        }
    }

    //int array[]={9,9,2,2,3,2,9,4,3,3};
    int array[]={5,5,5,0};
    cout<<sol.singleNumber2(array, 4)<<endl;
    cout<<sol.getSingle(array, 4)<<endl;
    DWORD end_time=GetTickCount();
    clock_t cend_time=clock();
    cout<< "Running time is: "<<static_cast<double>(cend_time-cstart_time)/CLOCKS_PER_SEC*1000<<"ms"<<endl;//输出运行时间
    cout<<"The run time is:"<<(end_time-start_time)<<"ms!"<<endl;//输出运行时间
    return 0;
}
