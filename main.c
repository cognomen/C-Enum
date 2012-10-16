#include "id.h"
#include "enum.h"

#include <stdio.h>

/****************************************************************/
#define SHAPE_POINTS(_, _V) \
    _V(LINE, 2) \
    _(TRIANGLE) \
    _(TETRAGON) \
    _(PENTAGON) \
    _V(SEPTAGON, 7) \

ENUM(SHAPE_POINTS);
ENUM_IMPL(SHAPE_POINTS);
ENUM_DEFINE_TOSTRING(SHAPE_POINTS, Shape_ToString)

ENUM_DECLARE_ITERATOR(SHAPE_POINTS,
                      Shape_IteratorBegin,
                      Shape_IteratorEnd,
                      Shape_IteratorToValue);

ENUM_DEFINE_ITERATOR(SHAPE_POINTS,
                     Shape_IteratorBegin,
                     Shape_IteratorEnd,
                     Shape_IteratorToValue)

void Shape_PrintAll(void)
{
    SHAPE_POINTS_Iterator_t iter = Shape_IteratorBegin();
    SHAPE_POINTS_Iterator_t end = Shape_IteratorEnd();

    while (iter <= end)
    {
        enum SHAPE_POINTS id = Shape_IteratorToValue(iter);
        printf("A %s has %d sides.\n", Shape_ToString(id), id);

        iter++;
    }
}

/* @bug Doesn't print final enum element */
void Shape_PrintAllRev(void)
{
    SHAPE_POINTS_Iterator_t iter = Shape_IteratorEnd();
    SHAPE_POINTS_Iterator_t begin = Shape_IteratorBegin();

    while (iter >= begin)
    {
        enum SHAPE_POINTS id = Shape_IteratorToValue(iter);
        printf("A %s has %d sides.\n", Shape_ToString(id), id);

        iter--;
    }
}

/**
 * ToString implemented using Iterators
 */
char const * Shape_AnotherToString(enum SHAPE_POINTS literal)
{
    SHAPE_POINTS_Iterator_t iter = Shape_IteratorBegin();
    SHAPE_POINTS_Iterator_t end = Shape_IteratorEnd();

    while (iter <= end)
    {
        if (Shape_IteratorToValue(iter) == literal)
        {
            return SHAPE_POINTS_IMPL[iter].name;
        }
        iter++;
    }

    return "UNKNOWN SHAPE";
}

/****************************************************************/
void Hex_PrintAll(void)
{
    HEX_Iterator_t iter;

    for (iter = Hex_IteratorBegin();
         iter < Hex_IteratorEnd();
         iter++)
    {
        enum HEX id = Hex_IteratorToValue(iter);
        printf("%s = %d\n", Hex_ToString(id), id);
    }

    /* Picks up the enum name that first matches HEX_MAX */
    printf("%s = %d\n", Hex_ToString(HEX_MAX), HEX_MAX);
}

/****************************************************************/

void local_enum(void)
{
    ENUM(SHAPE_POINTS);

    enum SHAPE_POINTS points = TETRAGON;

    switch (points)
    {
        case TRIANGLE:
            printf("A Triangle\n");
            break;
        case TETRAGON:
            printf("A Tetragon\n");
            break;
        default:
            printf("Unknown Shape");
    }
}

int main(void)
{
    Shape_PrintAll();
    Shape_PrintAllRev();

    printf("A %s has %d sides.\n", Shape_ToString(TETRAGON), TETRAGON);

    Hex_PrintAll();
}

