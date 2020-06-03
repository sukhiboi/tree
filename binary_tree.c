#include <stdlib.h>
#include "binary_tree.h"

Node create_node(Element e)
{
    Node new_node = malloc(sizeof(node));
    new_node->element = e;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

void insert_node(Node root, Comparer compare, Element e)
{
    Node *p_walker = &root;
    while (*p_walker != NULL)
    {
        if (compare(e, (*p_walker)->element))
            p_walker = &(*p_walker)->left;
        else
            p_walker = &(*p_walker)->right;
    }
    *p_walker = create_node(e);
}