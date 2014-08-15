#include <iostream>

using namespace std;
#define INT_MIN -1000
int find_max_len_method2(const int *A, int N) {
  int* max_len = new int[N]; // max_len[i]表示以A[i]结尾的那些子序列中的最长长度
  max_len[0] = 1;
  for(int i=1; i<N; i++) { // 依次考虑以A[1],...,A[N-1]结尾的子序列
    max_len[i] = 1;
    for(int j=0; j<i; j++) {
       if(A[i] > A[j]) {
         max_len[i] = max_len[j]+1>max_len[i] ? (max_len[j]+1):max_len[i];
       }
    }
  }
  cout << "max_len" << endl;
  for(int i=0; i<N; i++)
    cout << max_len[i] << " ";
  cout << endl;


  int result = 0;
  for(int i=0; i<N; i++)
    result = max_len[i]>result ? max_len[i]:result;
  delete[] max_len;
  return result;
}

int find_max_len_method3(const int *A, int N) {
  int* len_min_value = new int[N+1];
  int max_len;
  len_min_value[0] = INT_MIN;
  len_min_value[1] = A[0];
  max_len = 1;

  int p, r, m;//for binary search
  for(int i=1; i<N; i++) { // 依次引入A[1],...,A[N-1]
    p=0;
    r = max_len;
    while(p<=r)
    {
        m = (p+r)/2;
        if(len_min_value[m]<A[i])
        {
            p = m+1;
        }else{
            r = m-1;
        }
    }
    len_min_value[p]=A[i];

    if(p>max_len) max_len++;

    /*if(A[i] > len_min_value[max_len]) {
      max_len++;
      len_min_value[max_len] = A[i];
    }
    else {
      int j = max_len-1;
      while(A[i] < len_min_value[j])
        j--;
      len_min_value[j+1] = A[i];
    }*/
  }
  cout << "len_min_value:";
  for(int i=0; i<N+1; i++)
    cout << i<<" "<< len_min_value[i] <<endl;
  cout << endl;
  delete []len_min_value;
  return max_len;
}
#define len 8
int main() {

  //int a[len] = {1, -1, 2, -3, 4, -5, 6, -7,9}; // 1,2,4,6
  int a[len] = {100, 1, 80, 110, 97, 90, 99, 10}; // 1,2,4,6
  cout << "数组：" << endl;
  for(int i=0; i<len; i++)
    cout << a[i] << " ";
  cout << endl;
  cout << "数组的最长递增子序列长度为：" << find_max_len_method2(a, len) << endl;
  cout << "数组的最长递增子序列长度为：" << find_max_len_method3(a, len) << endl;
  return 0;
}
