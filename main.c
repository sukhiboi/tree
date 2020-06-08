#include <stdlib.h>
#include "binary_tree.h"

Element create_int_element(int);
Equality int_comparer(Element, Element);
void display(Node);

Element create_int_element(int value)
{
    Int element = malloc(sizeof(int));
    *element = value;
    return element;
}

Equality int_comparer(Element e1, Element e2)
{
    if (*(Int)(e1) == *(Int)(e2))
        return Equal;
    if (*(Int)(e1) < *(Int)(e2))
        return Less;
    return Greater;
}

void display(Node e)
{
    printf("%d ", *(Int)(e->element));
}

Element copy(Element e)
{
    return create_int_element(*(Int)(e));
}

int main()
{
    Node tree = create_node(create_int_element(10));
    insert_node(tree, int_comparer, create_int_element(5));
    insert_node(tree, int_comparer, create_int_element(20));
    insert_node(tree, int_comparer, create_int_element(3));
    insert_node(tree, int_comparer, create_int_element(1));
    print_in_order(balance(tree, int_comparer), display);
    return 0;
}