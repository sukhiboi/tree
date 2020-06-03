#include <stdlib.h>
#include "binary_tree.h"

typedef int *Int;

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

int main()
{
    //5, 3, 8, 1, 4, 7, 9
    Node tree = create_node(create_int_element(5));
    insert_node(tree, int_comparer, create_int_element(3));
    insert_node(tree, int_comparer, create_int_element(8));
    insert_node(tree, int_comparer, create_int_element(1));
    insert_node(tree, int_comparer, create_int_element(4));
    insert_node(tree, int_comparer, create_int_element(7));
    insert_node(tree, int_comparer, create_int_element(9));
    printf("%d\n", search(tree, int_comparer, create_int_element(2)));
    return 0;
}