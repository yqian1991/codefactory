#include <stdio.h>
#include <stdlib.h>
#include "structure.h"

int main()
{
    printf("start to create b-tree:\n");
    BiTree bt ;
    bt = initTree(bt);
    bt = createTree(bt);
    preTraverse(bt);
    return 0;
}
BiTNode *initTree(BiTNode *btree)
{
    btree = NULL;

    return btree;
}
BiTNode *createTree(BiTNode *btree)
{
    int ch;
    scanf("%d",&ch);

    if(ch==0)
    {
        btree = NULL;
    }
    else
    {
        btree = (BiTNode*) malloc(sizeof(BiTNode));
        //if(!btree)
           // exit(0);//内存分配失败则退出

        btree->data = ch;

        printf("建立%d的左子树：",btree->data);
        btree->left = createTree(btree->left);

        printf("建立%d的右子树：",btree->data);
        btree->right = createTree(btree->right);
    }
    return btree;
}
void preTraverse(BiTNode *btree)
{
    if(btree!=NULL)
    {
        printf("%d",btree->data);
        preTraverse(btree->left);
        preTraverse(btree->right);
    }
}
void printTree(BiTNode *btree, int i)
{
    if(btree != NULL)
     printTree(btree->left,i+5);

    if (btree->data)
     printf("%*c\n",i,btree->data);

    if(btree != NULL)
     printTree(btree->right,i+5);

     i=i-5;
}
