#ifndef STRUCTURE_H_INCLUDED
#define STRUCTURE_H_INCLUDED

typedef int ElementType;

typedef struct node
{
    ElementType data;
    struct node *left;
    struct node *right;
    //struct node *parent;

}BiTNode, *BiTree;

BiTNode *initTree(BiTNode *btree);
BiTNode *createTree(BiTNode *btree);
void printTree(BiTNode *btree, int i);
void preTraverse(BiTNode *btree);
#endif // STRUCTURE_H_INCLUDED
