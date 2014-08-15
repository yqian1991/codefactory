#ifndef CYCLE_H_INCLUDED
#define CYCLE_H_INCLUDED

#include <iostream>
#include <string>
#include <vector>


using namespace std;

struct ListNode {
     int val;
     ListNode *next;
     ListNode(int x) : val(x), next(NULL) {}
 };

class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        if (head == NULL)
            return NULL;
        ListNode *ptr1=head, *ptr2=head;
        while(true){
            ListNode *prev = ptr2;
            ptr1 = ptr1->next;
            if(ptr2->next != NULL)
            {
                ptr2 = ptr2->next->next;
                cout<<ptr1->val<<" "<<ptr2->val<<endl;
            }else
            {
                cout<<"ptr2.next is null"<<endl;
                return NULL;
            }

            if( ptr1==NULL || ptr2 == NULL)
            {
                cout<<"ptr1 or ptr2 reach end."<<endl;
                return NULL;
            }
            if(ptr1==ptr2)
            {
                cout<<"Node is:"<<prev->val<<endl;
                ptr1 = head;
                while(true)
                {
                    ptr1 = ptr1->next;
                    ptr2 = ptr2->next;
                    if( ptr1 == ptr2)
                    {
                        return ptr1;

                    }
                }
                //return prev;
            }
        }
    }

    /*vector<string> wordBreak(string s, unordered_set<string> &dict) {
        for(int i=0; i<s.size(); i++)
        {

        }
    }*/

    int singleNumber(int A[], int n) {
        int count[32] = {0};
        int result = 0;
        for (int i = 0; i < 32; i++) {
            for (int j = 0; j < n; j++) {
                if ((A[j] >> i) & 1) {
                    count[i]++;
                }
            }
            result |= ((count[i] % 3) << i);
        }
        return result;
    }

    int singleNumber2(int A[], int n) {
        int ones = 0, twos = 0, threes = 0;
        for (int i = 0; i < n; i++) {
            twos |= ones & A[i];
            ones ^= A[i];
            threes = ones & twos;
            cout<< ones <<" "<<twos<<" "<<threes<<endl;
            ones &= ~threes;
            twos &= ~threes;
            cout<< ones <<" "<<twos<<" "<<threes<<endl;
            cout<<"-------------------------\n";
        }
        return ones;
    }
    int getSingle(int arr[], int n)
    {
    // Initialize result
    int result = 0;

    int x, sum;

    // Iterate through every bit
    for (int i = 0; i < 32; i++)
    {
      // Find sum of set bits at ith position in all
      // array elements
      sum = 0;
      x = (1 << i);
      for (int j=0; j< n; j++ )
      {
          if (arr[j] & x)
            sum++;
      }

      // The bits with sum not multiple of 3, are the
      // bits of element with single occurrence.
      if (sum % 3)
        result |= x;
    }

    return result;
    }

    vector<int> twoSum(vector<int> &numbers, int target) {
        sort
    }

};



#endif // CYCLE_H_INCLUDED
