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
typedef int *int_ptr;
typedef struct node
{
    Element element;
    struct node *left;
    struct node *right;
} node;

typedef node *node_ptr;
typedef Equality (*Comparer)(Element, Element);
typedef void (*Displayer)(node_ptr);
typedef Element (*Copier)(Element);

node_ptr create_node(Element);
void insert_node(node_ptr, Comparer, Element);
void print_in_order(node_ptr, Displayer);
void print_pre_order(node_ptr, Displayer);
void print_post_order(node_ptr, Displayer);
Bool search(node_ptr, Comparer, Element);
node_ptr right_rotate(node_ptr node_to_rotate);
node_ptr left_rotate(node_ptr node_to_rotate);
node_ptr delete (node_ptr root, node_ptr node_to_delete, Comparer compare, Copier copy);
node_ptr balance(node_ptr root, Comparer compare);
node_ptr balance_with_rotation(node_ptr root, Comparer compare);

#endif
