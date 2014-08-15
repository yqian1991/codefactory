#include <stdio.h>
#include <stdlib.h>

const int MAXNUM = 100;
const int MAXINT = 999999;

void Dijkstra(int edge[MAXNUM][MAXNUM], int ptNum, int v, int *prev, int *dist)
{//v is the start point, dist[i] is the distance from v to point i.
    int isVisited[MAXNUM];//judge whether a point visited or not:1 visited, 0 not;
    //printf("edge %d\n",edge[4][5]);
    int i=1,j=1;
    for(i=1;i<=ptNum;++i)
    {
        dist[i]=edge[v][i];
        isVisited[i]=0;//all not visited at first

        if(dist[i] == MAXINT)
            prev[i] = 0;
        else
            prev[i] = v;
    }

    //start finding from v
    dist[v]=0;
    isVisited[v]=1;
    for(i=2;i<=ptNum;++i)
    {
        //find the shortest dist first
        int tmp=MAXINT;
        int u=v;
        for(j=1;j<=ptNum;++j)
        {
            if( (isVisited[j]==0) && dist[j]<tmp )
            {
                u=j;
                tmp=dist[j];
            }
        }//after this cycle, we find the current shortest dist it's point is u
        isVisited[u]=1;

        //after find u, we need to update the dist
        for(j=1;j<=ptNum;++j)
        {
            if( (isVisited[j]==0) && edge[u][j]<MAXINT )
            {
                int newdist=dist[u]+edge[u][j];
                if( newdist<dist[j])
                {
                    dist[j]=newdist;
                    prev[j]=u;
                }
            }
        }
    }
    printf("%d\n",dist[ptNum]);
}

void searchPath(int *prev, int v, int u)
{
    int que[MAXNUM];//the needed path
    int index=1;
    que[index]=u;//end point. then use prev[] to find prior point

    int tmp=prev[u];
    while( tmp!= v)//means path not over
    {
        que[++index]=tmp;
        tmp=prev[tmp];
    }
    que[++index]=v;
    int i=0;
    for(i=index;i>0;i--)
    {
        if( i!=1 )
        {
            printf("%d->",que[i]);
        }else
        {
            printf("%d.\n",que[i]);
        }

    }
}
int main()
{

    int ptNum=MAXNUM;//the number of points in the graph;
    int edgeNum=MAXNUM;//the number of edges in the graph
    int edge[MAXNUM][MAXNUM];//store the weights of each edges in graph
    int i=0,j=0,p=0,q=0,weight=0;

    int dist[MAXNUM];// 表示当前点到源点的最短路径长度
    int prev[MAXNUM];// 记录当前点的前一个结点

    printf("Enter points number:");
    scanf("%d",&ptNum);
    printf("Enter edges number:");
    scanf("%d",&edgeNum);
    //can write a  function to verify the numbers valid or not.
    if( (2*edgeNum)>(ptNum*(ptNum-1)) )//means invalid edge number according to points number
    {
        printf("Invalid edges number according to your points number\n");
        return 0;
    }else
    {
        printf("there are %d points and %d edges in the graph.\n",ptNum,edgeNum);
    }

    //initial all edges weights to 0
    for(i=1;i<=ptNum;i++)
    {
        for(j=1;j<=ptNum;j++)
        {
            edge[i][j]=MAXINT;
        }
    }
    //fill the edge table with weights
    printf("input weights of %d edges.\n",edgeNum);
    for (i=1;i<=edgeNum;i++)
    {
        printf("edge %d:",i);
        scanf("%d",&p);//point p;
        scanf("%d",&q);//point q;
        scanf("%d",&weight);//weight of edeg (p-q);
        edge[p][q]=weight;
    }
    printf("edges input over.\n");

    Dijkstra(edge, ptNum, 1, prev, dist);
    printf("dist is %d, print path:\n", dist[ptNum]);

    int k=0;
    for(k=1;k<=ptNum;k++)
    {
        printf("%d ",prev[k]);
    }
    printf("\n");
    searchPath(prev, 1, ptNum);
    return 0;
}
