#include <stdio.h>
//�ҳ�����ȫ����
int n = 0;
//C���Ե�����������������ָ��ʵ��
void swap(int *a, int *b)
{
    int m;
    m = *a;
    *a = *b;
    *b = m;
}
//�����㷨
//���ع�עKֵ�ı仯��iֵֻ�Ǻ����ľֲ�����
void perm(int list[], int k, int m)
{
    int i;
    if(k > m)
    {
        for(i = 0; i <= m; i++)
            printf("%d ", list[i]);
        printf("\n");
        n++;
    }
    else
    {
        for(i = k; i <= m; i++)
        {
            printf("i=%d,k=%d.\n",i,k);
            swap(&list[k], &list[i]);
            perm(list, k + 1, m);
            swap(&list[k], &list[i]);
        }
    }
}

int main()
{
    int list[] = {1, 2, 3, 4};
    perm(list, 0, 3);
    printf("total:%d\n", n);
    return 0;
}
