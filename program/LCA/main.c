#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode
{
  struct TreeNode*left;
  struct TreeNode* right;
  int value;
}TNode, *Node;

int Find(Node p, int p1, int p2, Node* res)
{
    if(p == NULL)
		return 0;
	int r1 = 0;
	int r2 = 0;
	Node tmp = NULL;
	if(p->left)
	{
		r1  = Find(p->left,p1,p2,&tmp);
		if(r1 == -2)
		{
			*res = p;
			return -1;
		}
		if(r1 == -1)
		{
			*res = tmp;
			return -1;
		}
	}
	if(p->right)
	{
		r2  = Find(p->right,p1,p2,&tmp);
		if(r2 == -2)
		{
			*res = p;
			return -1;
		}
		if(r2 == -1)
		{
			*res = tmp;
			return -1;
		}
	}
	if(r1 == 1 && r2 == 1)
	{
		*res = p;
		return -1;
	}
	int r = 0;
	if(p->value == p1 || p->value == p2)
		r = 1;
	if((r1 == 1 || r2 == 1) && r == 1)
	{
		return -2;
	}
	if(r1 == 1 || r2 == 1)
		return 1;
	return r;
}

Node Insert(Node T, int value)
{
   if(T == NULL)
   {
       T = (Node)malloc(sizeof(struct TreeNode));
       if( T == NULL)
          printf("Malloc Failed.");
       else
       {
          T->value  = value;
          T->left = T->right = NULL;
       }
   }
   else if(value < T->value)
         T->left = Insert(T->left,value);
   else if(value > T->value)
     T->right = Insert(T->right, value);
  return T;
 }

Node MakeEmpty(Node T)
{
	if(T != NULL)
	{
		MakeEmpty(T->left);
		MakeEmpty(T->right);
		free(T);
	}
	return NULL;
}

int main()
{
	Node T = NULL;
	T = Insert(T,45);
	T = Insert(T,21);
	T = Insert(T,65);
	T = Insert(T,10);
	T = Insert(T,50);
    T = Insert(T,70);
	T = Insert(T,24);
	Node res = NULL;
    int ret = Find(T,10,21,&res);
	if(ret == -1)
		printf("%d /n",res->value);
    return 0;
}
