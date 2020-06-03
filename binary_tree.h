#include <stdio.h>
#include <stdlib.h>

#ifndef __BINARYTREE_H_
#define __BINARYTREE_H_

typedef enum
{
    False,
    True
} Bool;

typedef void *Element;

typedef struct node
{
    Element element;
    struct node *left;
    struct node *right;
} node;

typedef node *Node;
typedef Bool (*Comparer)(Element, Element);

Node create_node(Element);
Node insert_node(Node, Comparer, Element);
Bool search(Node, Comparer, Element);
void print_in_order(Node);
void print_pre_order(Node);
void print_post_order(Node);
#endif