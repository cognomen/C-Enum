#include <stdio.h>
#include "shape.h"

ENUM_IMPL(SHAPE);
ENUM_DEFINE_ITERATOR(SHAPE,
                     Shape_IteratorBegin,
                     Shape_IteratorEnd,
                     Shape_IteratorToValue)

int main(void)
{
    SHAPE_Iterator_t iter = Shape_IteratorBegin();
    SHAPE_Iterator_t end = Shape_IteratorEnd();

    while (iter <= end)
    {
        enum SHAPE shape = Shape_IteratorToValue(iter);
        printf("%s sides: %d.\n", Shape_ToString(shape), shape);
        iter++;
    }

    return 0;
}
