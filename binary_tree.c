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
        p_walker = &(*p_walker)->right;
        Equality result = compare(e, (*p_walker)->element);
        if (result == Equal)
            return True;
        if (result == Less)
            p_walker = &(*p_walker)->left;
    }
    return False;
}

Node get_parent(Node root, Element e, Comparer compare)
{
    Bool left_child_check = root->left != NULL && root->left->element == e;
    Bool right_child_check = root->right != NULL && root->right->element == e;
    if (left_child_check || right_child_check)
        return root;
    if (compare(e, root->element) == Less)
        return get_parent(root->left, e, compare);
    return get_parent(root->right, e, compare);
}

Node get_max_node(Node root)
{
    if (root->right == NULL)
        return root;
    return get_max_node(root->right);
}

Node get_min_node(Node root)
{
    if (root->left == NULL)
        return root;
    return get_min_node(root->left);
}

Node get_compatible_node(Node root)
{
    if (root->left != NULL)
        return get_max_node(root->left);
    if (root->right != NULL)
        return get_min_node(root->right);
    return root;
}

void free_node(Node node)
{
    free(node->element);
    free(node);
}

Bool is_leaf_node(Node root)
{
    return root->right == NULL && root->left == NULL;
}

void delete_leaf_node(Node parent, Node to_be_deleted, Comparer compare)
{
    if (parent->left != NULL && parent->left == to_be_deleted)
        parent->left = NULL;
    if (parent->right != NULL && parent->right == to_be_deleted)
        parent->right = NULL;
    free_node(to_be_deleted);
}

Node delete (Node root, Node node_to_delete, Comparer compare, Copier copy)
{
    Node compatible_node = get_compatible_node(node_to_delete);
    Node parent = get_parent(root, compatible_node->element, compare);
    free(node_to_delete->element);
    node_to_delete->element = copy(compatible_node->element);
    if (is_leaf_node(compatible_node))
    {
        delete_leaf_node(parent, compatible_node, compare);
        return root;
    }
    return delete (root, compatible_node, compare, copy);
}

Node right_rotate(Node node_to_rotate)
{
    if (node_to_rotate == NULL || node_to_rotate->left == NULL)
        return node_to_rotate;
    Node node_to_rotate_left = node_to_rotate->left;
    node_to_rotate->left = node_to_rotate_left->right;
    node_to_rotate_left->right = node_to_rotate;
    return node_to_rotate_left;
}

Node left_rotate(Node node_to_rotate)
{
    if (node_to_rotate == NULL || node_to_rotate->right == NULL)
        return node_to_rotate;
    Node node_to_rotate_right = node_to_rotate->right;
    node_to_rotate->right = node_to_rotate_right->left;
    node_to_rotate_right->left = node_to_rotate;
    return node_to_rotate_right;
}

void count_nodes(Node root, Int count)
{
    if (root == NULL)
        return;
    count_nodes(root->left, count);
    *count = *count + 1;
    count_nodes(root->right, count);
}

void store_nodes_in_order(Node *array, Node root, int *index)
{
    if (root == NULL)
        return;
    store_nodes_in_order(array, root->left, index);
    array[*index] = root;
    *index = *index + 1;
    store_nodes_in_order(array, root->right, index);
}

Node *get_node_in_order(Node root, Int index)
{
    Int node_count = malloc(sizeof(Int));
    *node_count = 0;
    count_nodes(root, node_count);
    Node *nodes = malloc(sizeof(Node) * (*node_count));
    store_nodes_in_order(nodes, root, index);
    return nodes;
}

Node perform_balance(Node *nodes, int start_idx, int end_idx, Comparer compare)
{
    if (start_idx > end_idx)
        return NULL;
    int mid_idx = (int)(start_idx + end_idx) / 2;
    Node root = create_node(nodes[mid_idx]->element);
    root->left = perform_balance(nodes, start_idx, mid_idx - 1, compare);
    root->right = perform_balance(nodes, mid_idx + 1, end_idx, compare);
    return root;
}

Node balance(Node root, Comparer compare)
{
    Int index = malloc(sizeof(int));
    *index = 0;
    Node *nodes = get_node_in_order(root, index);
    return perform_balance(nodes, 0, *index - 1, compare);
}

int max(int x, int y)
{
    if (x > y)
        return x;
    else
        return y;
}

int get_tree_depth(Node root)
{
    if (root == NULL)
        return 0;
    int left_tree_depth = get_tree_depth(root->left);
    int right_tree_depth = get_tree_depth(root->right);
    return max(left_tree_depth, right_tree_depth) + 1;
}

Bool get_balance_factor(Node root)
{
    int left_tree_depth = get_tree_depth(root->left);
    int right_tree_depth = get_tree_depth(root->right);
    return right_tree_depth - left_tree_depth;
}

Node balance_with_rotation(Node root, Comparer compare)
{
    if (root == NULL)
        return root;
    int balance_factor = get_balance_factor(root);
    if (balance_factor >= -1 && balance_factor <= 1)
    {
        root->left = balance_with_rotation(root->left, compare);
        root->right = balance_with_rotation(root->right, compare);
        return root;
    }
    root = balance_factor < 0 ? right_rotate(root) : left_rotate(root);
    return balance_with_rotation(root, compare);
}