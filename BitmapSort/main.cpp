#include <iostream>
#include <memory.h>
#include <vector>

using namespace std;

#define BYTESIZE 8 //meas every char in p has 8 bit
void SetBit(char *p, int posi)
{
    for(int i=0; i <(posi/BYTESIZE); i++)
    {
        p++;
    }

    *p = *p|(0x01 <<(posi%BYTESIZE));//将该Bit位赋值1
    return;
}

void BitMapSortDemo()
{
    //为了简单起见，我们不考虑负数
    int num[] = {3,5,2,10,6,12,8,14,9,34,19,78};

    //BufferLen这个值是根据待排序的数据中最大值确定的
    //待排序中的最大值是14，因此只需要2个Bytes(16个Bit)
    //就可以了。
    const int BufferLen = 10;
    char *pBuffer = new char[BufferLen];

    //要将所有的Bit位置为0，否则结果不可预知。
    memset(pBuffer,0,BufferLen);
    for(int i=0;i<12;i++)
    {
        //首先将相应Bit位上置为1
        SetBit(pBuffer,num[i]);
    }

    //输出排序结果
    for(int i=0;i<BufferLen;i++)//每次处理一个字节(Byte)
    {
        for(int j=0;j<BYTESIZE;j++)//处理该字节中的每个Bit位
        {
            //判断该位上是否是1，进行输出，这里的判断比较笨。
            //首先得到该第j位的掩码（0x01＜＜j），将内存区中的
            //位和此掩码作与操作。最后判断掩码是否和处理后的
            //结果相同
            if((*pBuffer&(0x01<<j)) == (0x01<<j))
            {
                cout<<i*BYTESIZE + j<<" ";
            }
        }
        pBuffer++;
    }
    cout<<endl;
}

void createCounter(vector<int>& counter, int n)
{
    vector<int> primes;
    counter.resize(n + 1, 0);
    counter[1] = 1;

    for(int i = 2; i <= n; i++)
    {
        if (counter[i] == 0)
        {
            counter[i] = i + 1;
            primes.push_back(i);
        }

        for(size_t j = 0; j < primes.size(); j++)
        {
            if (primes[j] * i > n)
                break;

            if (i % primes[j] == 0)
            {
                int k = i;
                int l = primes[j] * primes[j];

                while(k % primes[j] == 0)
                {
                    l *= primes[j];
                    k /= primes[j];
                }

                counter[primes[j] * i] = counter[k] * (l - 1) / (primes[j] - 1);
                break;
            }
            else
                counter[primes[j] * i] = counter[i] * (primes[j] + 1);
        }
    }
}

void testCreateCounter()
{
    int max = 5000000;
    vector<int> counter;
    createCounter(counter, max);

    for (size_t i = 0; i < counter.size(); i++)
    {
        size_t num = counter[i] - i;
        if (num < counter.size() && num > i && counter[num] == counter[i])
            cout << i << " " << num << endl;
    }
}

int main()
{
    BitMapSortDemo();
    testCreateCounter();
    return 0;
}
