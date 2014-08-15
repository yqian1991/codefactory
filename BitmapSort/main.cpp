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

    *p = *p|(0x01 <<(posi%BYTESIZE));//����Bitλ��ֵ1
    return;
}

void BitMapSortDemo()
{
    //Ϊ�˼���������ǲ����Ǹ���
    int num[] = {3,5,2,10,6,12,8,14,9,34,19,78};

    //BufferLen���ֵ�Ǹ��ݴ���������������ֵȷ����
    //�������е����ֵ��14�����ֻ��Ҫ2��Bytes(16��Bit)
    //�Ϳ����ˡ�
    const int BufferLen = 10;
    char *pBuffer = new char[BufferLen];

    //Ҫ�����е�Bitλ��Ϊ0������������Ԥ֪��
    memset(pBuffer,0,BufferLen);
    for(int i=0;i<12;i++)
    {
        //���Ƚ���ӦBitλ����Ϊ1
        SetBit(pBuffer,num[i]);
    }

    //���������
    for(int i=0;i<BufferLen;i++)//ÿ�δ���һ���ֽ�(Byte)
    {
        for(int j=0;j<BYTESIZE;j++)//������ֽ��е�ÿ��Bitλ
        {
            //�жϸ�λ���Ƿ���1�����������������жϱȽϱ���
            //���ȵõ��õ�jλ�����루0x01����j�������ڴ����е�
            //λ�ʹ������������������ж������Ƿ�ʹ�����
            //�����ͬ
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
