#include <iostream>

using namespace std ;

int a[100];

void heap(int s, int n)//nΪԪ���ܸ���
{//������,ʹ��ʼ��ΪС����
    int i, j = 1, k = a[s], max = 0 ;
    while(j!=max)
    {
        i = a[s] ;
        j = max ;
        if(s*2<=n)
            if(a[s*2]<i)
            {
                i = a[s*2] ;
                j = s * 2 ;
            }
        if(s*2+1<=n)
            if(a[s*2+1]<i)
            {
                i = a[s*2+1] ;
                j = s*2+1 ;
            }
        if(j!=max)
        {
            a[s] = i ;
            s = j ;
        }
        a[s] = k ;
    }
}
int main()
{
    int n, i ;
    cout<<"���������Сn��";
    cin >> n ;
    for(i=1; i<=n; i++)
        cin >> a[i] ;

    for(i=n/2; i>0; i--)//����С����
        heap(i, n) ;

    for(i=n; i>1; i--)
    {
        cout << a[1] << " " ;
        a[1] = a[i] ;
        n -- ;
        heap(1, n);//������ǰ��
    }
    cout << a[1] << " " ;       //�������Ԫ��
    return 0 ;
}
