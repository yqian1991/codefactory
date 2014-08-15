#include <iostream>
#include <cstdio>
#include <ctime>
#include <cstdlib>
#include <cmath>

using namespace std;

int rand5()
{
    //随机生成[1-5]之间的随机数
    return (rand() % 5 + 1);
}

int rand7_1()
{
    //随机生成[1-7]之间的随机数
    int a;
    while((a = rand5() * 5 + rand5()) > 26);
    return (a - 3)/3;
}

int rand7_2()
{
    //随机生成[1-7]之间的随机数
    int num = rand5() + rand5() * 10 + rand5() * 100 + rand5() * 1000;
    return (num % 7 + 1);
}

int rand7_3()
{
    return (rand() % 7 + 1);
}

double variance(int *a, int average, int len)
{
    //求方差：sqrt(sum((a[i]-平均数)^2))
    double s = 0;
    for(int i = 1; i < len; i++)
    {
        s += (a[i] - average) * (a[i] - average) ;
    }
    return sqrt(s);
}

int main()
{
    srand((unsigned)time(NULL));
    int cnt = 1000;
    int a[8] = {0};
    int b[8] = {0};
    int c[8] = {0};
    int a1, a2, a3;
    int ave = cnt / 7;
    while(cnt--)
    {
        a1 = rand7_1();
        a2 = rand7_2();
        a3 = rand7_3();
        a[a1]++;
        b[a2]++;
        c[a3]++;
    }
    cout << "The variance of rand7_1(): " << variance(a, ave, 8) << endl;
    cout << "The variance of rand7_2(): " << variance(b, ave, 8) << endl;
    cout << "The variance of rand7_2(): " << variance(c, ave, 8) << endl;
}
