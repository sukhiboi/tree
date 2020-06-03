#include <stdlib.h>
#include "binary_tree.h"

typedef int *Int;

Element create_int_element(int);
Bool int_comparer(Element, Element);
void display(Node);

Element create_int_element(int value)
{
    Int element = malloc(sizeof(int));
    *element = value;
    return element;
}

Bool int_comparer(Element e1, Element e2)
{
    return (*(Int)(e1) < *(Int)(e2));
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
    print_in_order(tree, display);
    printf("\n");
    print_pre_order(tree, display);
    printf("\n");
    print_post_order(tree, display);
    printf("\n");
    return 0;
}