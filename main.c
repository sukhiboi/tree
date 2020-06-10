#include <stdlib.h>
#include "binary_tree.h"

Element create_int_element(int);
Equality int_comparer(Element, Element);
void display(node_ptr);

Element create_int_element(int value)
{
    int_ptr element = malloc(sizeof(int));
    *element = value;
    return element;
}

Equality int_comparer(Element e1, Element e2)
{
    if (*(int_ptr)(e1) == *(int_ptr)(e2))
        return Equal;
    if (*(int_ptr)(e1) < *(int_ptr)(e2))
        return Less;
    return Greater;
}

void display(node_ptr e)
{
    printf("%d ", *(int_ptr)(e->element));
}

Element copy(Element e)
{
    return create_int_element(*(int_ptr)(e));
}

int main()
{
    node_ptr tree = create_node(create_int_element(7));
    insert_node(tree, int_comparer, create_int_element(6));
    insert_node(tree, int_comparer, create_int_element(5));
    insert_node(tree, int_comparer, create_int_element(4));
    insert_node(tree, int_comparer, create_int_element(3));
    insert_node(tree, int_comparer, create_int_element(2));
    insert_node(tree, int_comparer, create_int_element(1));
    node_ptr balanced_tree = balance_with_rotation(tree, int_comparer);
    print_in_order(balanced_tree, display);
    return 0;
}