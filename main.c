#include <stdlib.h>
#include "binary_tree.h"

typedef int *Int;

Element create_int_element(int);
Bool int_comparer(Element, Element);

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

int main()
{
    Node tree = create_node(create_int_element(12));
    return 0;
}