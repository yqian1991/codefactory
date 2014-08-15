#include <iostream>

using namespace std;

const int i =100;
const int MAX = 3;

int main()
{
    int const c=10;
    int d=11;
    const int *a1 = &c;//point to constant
    int const *a2 = &c;//constant can't be changed
    int * const a3= &d;//point to address, pointer can't be changed
    a1=&c;//because constant can't be changed
    *a3=d;//can change the constant value, but not the pointer
    cout<<*a3<<endl;
    cout << "Hello world!" << endl;

    int var[MAX]={10, 20, 30};
    int *ptr[MAX];
    for(int i=0; i<MAX; i++){
        ptr[i] = &var[i];
        cout<<*ptr[i]<<endl;
    }

    double* pvalue = NULL;
    if ( !(pvalue = new double))
    {

        cout<<"memory error"<<endl;
    }
    delete pvalue;

    double(*p) [3];
    double array[3]={1.0, 2.0, 3.0};
    double a = 1.9;
    double b = 2.1;
    double dd = 3.2;
    //p[0] = &a;
    p=array;

    return 0;
}
