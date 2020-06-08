#include <stdio.h>
#include <stdlib.h>

#ifndef __BINARYTREE_H_
#define __BINARYTREE_H_

typedef enum
{
    False,
    True
} Bool;

typedef enum
{
    Less, 
    Equal, 
    Greater
} Equality;

typedef void *Element;
typedef int *Int;
typedef struct node
{
    Element element;
    struct node *left;
    struct node *right;
} node;

typedef node *Node;
typedef Equality (*Comparer)(Element, Element);
typedef void (*Displayer)(Node);
typedef Element (*Copier)(Element);

Node create_node(Element);
void insert_node(Node, Comparer, Element);
void print_in_order(Node, Displayer);
void print_pre_order(Node, Displayer);
void print_post_order(Node, Displayer);
Bool search(Node, Comparer, Element);
Node right_rotate(Node node_to_rotate);
Node left_rotate(Node node_to_rotate);
Node delete (Node root, Node node_to_delete, Comparer compare, Copier copy);
Node balance(Node root, Comparer compare);
Node balance_with_rotation(Node root, Comparer compare);

#endif