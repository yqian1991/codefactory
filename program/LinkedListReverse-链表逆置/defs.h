#ifndef DEFS_H_INCLUDED
#define DEFS_H_INCLUDED

typedef struct node
{
    int id;
    struct node *next;
}node;

typedef node *Linklist;

Linklist head;
node * p;

#endif // DEFS_H_INCLUDED
