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
        if (compare(e, (*p_walker)->element) == Less)
            p_walker = &(*p_walker)->left;
        else
            p_walker = &(*p_walker)->right;
    }
    *p_walker = create_node(e);
}

void print_in_order(Node root, Displayer display)
{
    if (root == NULL)
        return;
    print_in_order(root->left, display);
    display(root);
    print_in_order(root->right, display);
}
void print_pre_order(Node root, Displayer display)
{
    if (root == NULL)
        return;
    display(root);
    print_pre_order(root->left, display);
    print_pre_order(root->right, display);
}
void print_post_order(Node root, Displayer display)
{
    if (root == NULL)
        return;
    print_post_order(root->left, display);
    print_post_order(root->right, display);
    display(root);
}

Bool search(Node root, Comparer compare, Element e)
{
    Node *p_walker = &root;
    while (*p_walker != NULL)
    {
        Equality result = compare(e, (*p_walker)->element);
        if (result == Equal)
            return True;
        if (result == Less)
            p_walker = &(*p_walker)->left;
        else
            p_walker = &(*p_walker)->right;
    }
    return False;
}