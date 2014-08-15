#include <stdio.h>
#include <stdlib.h>

#define N 10000

int parent[N];

int findParent(int p)
{
    if (parent[p]<0) return p;
    return parent[p]=findParent(parent[p]);
}
int main()
{
    int edges;
    scanf("%d", &edges);
    memset(parent, -1, sizeof(parent));

    int i=0;
    for(i=0; i<edges; i++)
    {
        int a,b;
        scanf("%d %d", &a, &b);
        int p = findParent(a);
        int q = findParent(b);

        if( parent[p]<parent[q] )
        {
            parent[p] += parent[q];
            parent[q]=p;
        }
        else{
            parent[q] += parent[p];
            parent[p]=q;
        }

    }
    return 0;
}
