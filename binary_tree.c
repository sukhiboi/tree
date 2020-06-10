#include <stdlib.h>
#include "binary_tree.h"

node_ptr create_node(Element e)
{
    node_ptr new_node = malloc(sizeof(node));
    new_node->element = e;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

void insert_node(node_ptr root, Comparer compare, Element e)
{
    node_ptr *p_walker = &root;
    while (*p_walker != NULL)
    {
        if (compare(e, (*p_walker)->element) == Less)
            p_walker = &(*p_walker)->left;
        else
            p_walker = &(*p_walker)->right;
    }
    *p_walker = create_node(e);
}

void print_in_order(node_ptr root, Displayer display)
{
    if (root == NULL)
        return;
    print_in_order(root->left, display);
    display(root);
    print_in_order(root->right, display);
}
void print_pre_order(node_ptr root, Displayer display)
{
    if (root == NULL)
        return;
    display(root);
    print_pre_order(root->left, display);
    print_pre_order(root->right, display);
}
void print_post_order(node_ptr root, Displayer display)
{
    if (root == NULL)
        return;
    print_post_order(root->left, display);
    print_post_order(root->right, display);
    display(root);
}

Bool search(node_ptr root, Comparer compare, Element e)
{
    node_ptr *p_walker = &root;
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

node_ptr get_parent(node_ptr root, Element e, Comparer compare)
{
    Bool left_child_check = root->left != NULL && root->left->element == e;
    Bool right_child_check = root->right != NULL && root->right->element == e;
    if (left_child_check || right_child_check)
        return root;
    if (compare(e, root->element) == Less)
        return get_parent(root->left, e, compare);
    return get_parent(root->right, e, compare);
}

node_ptr get_max_node(node_ptr root)
{
    if (root->right == NULL)
        return root;
    return get_max_node(root->right);
}

node_ptr get_min_node(node_ptr root)
{
    if (root->left == NULL)
        return root;
    return get_min_node(root->left);
}

node_ptr get_compatible_node(node_ptr root)
{
    if (root->left != NULL)
        return get_max_node(root->left);
    if (root->right != NULL)
        return get_min_node(root->right);
    return root;
}

void free_node(node_ptr node)
{
    free(node->element);
    free(node);
}

Bool is_leaf_node(node_ptr root)
{
    return root->right == NULL && root->left == NULL;
}

void delete_leaf_node(node_ptr parent, node_ptr to_be_deleted, Comparer compare)
{
    if (parent->left != NULL && parent->left == to_be_deleted)
        parent->left = NULL;
    if (parent->right != NULL && parent->right == to_be_deleted)
        parent->right = NULL;
    free_node(to_be_deleted);
}

node_ptr delete (node_ptr root, node_ptr node_to_delete, Comparer compare, Copier copy)
{
    node_ptr compatible_node = get_compatible_node(node_to_delete);
    node_ptr parent = get_parent(root, compatible_node->element, compare);
    free(node_to_delete->element);
    node_to_delete->element = copy(compatible_node->element);
    if (is_leaf_node(compatible_node))
    {
        delete_leaf_node(parent, compatible_node, compare);
        return root;
    }
    return delete (root, compatible_node, compare, copy);
}

node_ptr right_rotate(node_ptr node_to_rotate)
{
    if (node_to_rotate == NULL || node_to_rotate->left == NULL)
        return node_to_rotate;
    node_ptr node_to_rotate_left = node_to_rotate->left;
    node_to_rotate->left = node_to_rotate_left->right;
    node_to_rotate_left->right = node_to_rotate;
    return node_to_rotate_left;
}

node_ptr left_rotate(node_ptr node_to_rotate)
{
    if (node_to_rotate == NULL || node_to_rotate->right == NULL)
        return node_to_rotate;
    node_ptr node_to_rotate_right = node_to_rotate->right;
    node_to_rotate->right = node_to_rotate_right->left;
    node_to_rotate_right->left = node_to_rotate;
    return node_to_rotate_right;
}

void count_nodes(node_ptr root, int_ptr count)
{
    if (root == NULL)
        return;
    count_nodes(root->left, count);
    *count = *count + 1;
    count_nodes(root->right, count);
}

void store_nodes_in_order(node_ptr *array, node_ptr root, int *index)
{
    if (root == NULL)
        return;
    store_nodes_in_order(array, root->left, index);
    array[*index] = root;
    *index = *index + 1;
    store_nodes_in_order(array, root->right, index);
}

node_ptr *get_node_in_order(node_ptr root, int_ptr index)
{
    int_ptr node_count = malloc(sizeof(int_ptr));
    *node_count = 0;
    count_nodes(root, node_count);
    node_ptr *nodes = malloc(sizeof(node_ptr) * (*node_count));
    store_nodes_in_order(nodes, root, index);
    return nodes;
}

node_ptr perform_balance(node_ptr *nodes, int start_idx, int end_idx, Comparer compare)
{
    if (start_idx > end_idx)
        return NULL;
    int mid_idx = (int)(start_idx + end_idx) / 2;
    node_ptr root = create_node(nodes[mid_idx]->element);
    root->left = perform_balance(nodes, start_idx, mid_idx - 1, compare);
    root->right = perform_balance(nodes, mid_idx + 1, end_idx, compare);
    return root;
}

node_ptr balance(node_ptr root, Comparer compare)
{
    int_ptr index = malloc(sizeof(int));
    *index = 0;
    node_ptr *nodes = get_node_in_order(root, index);
    return perform_balance(nodes, 0, *index - 1, compare);
}

int max(int x, int y)
{
    if (x > y)
        return x;
    else
        return y;
}

int get_tree_depth(node_ptr root)
{
    if (root == NULL)
        return 0;
    int left_tree_depth = get_tree_depth(root->left);
    int right_tree_depth = get_tree_depth(root->right);
    return max(left_tree_depth, right_tree_depth) + 1;
}

Bool get_balance_factor(node_ptr root)
{
    int left_tree_depth = get_tree_depth(root->left);
    int right_tree_depth = get_tree_depth(root->right);
    return right_tree_depth - left_tree_depth;
}

node_ptr balance_with_rotation(node_ptr root, Comparer compare)
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