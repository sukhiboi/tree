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