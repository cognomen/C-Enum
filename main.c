#include "id.h"
#include "enum.h"

#ifndef PREPROCESS
#   include <stdio.h>
#endif

/****************************************************************/
#define MY_ID(_, _V) \
    _V(MY_ID_0, 0) \
    _(MY_ID_GROUP1_START) \
    _V(MY_ID_GROUP1_0, MY_ID_GROUP1_START) \
    _(MY_ID_GROUP1_1) \
    _(MY_ID_GROUP1_2) \
    _(MY_ID_GROUP1_3) \
    _V(MY_ID_GROUP1_666, 666) \
    _(MY_ID_MAX) \

ENUM(MY_ID);
ENUM_IMPL(MY_ID);

ENUM_DECLARE_TOSTRING(MY_ID, MyId_ToString);

ENUM_DEFINE_TOSTRING(MY_ID, MyId_ToString)

ENUM_DECLARE_ITERATOR(MY_ID,
                      MyId_IteratorBegin,
                      MyId_IteratorEnd,
                      MyId_IteratorToValue);

ENUM_DEFINE_ITERATOR(MY_ID,
                     MyId_IteratorBegin,
                     MyId_IteratorEnd,
                     MyId_IteratorToValue)

void MyId_PrintAll(void)
{
    MY_ID_Iterator_t iter = MyId_IteratorBegin();
    MY_ID_Iterator_t end = MyId_IteratorEnd();

    while (iter != end)
    {
        enum MY_ID id = MyId_IteratorToValue(iter);
        printf("%s = %d\n", MyId_ToString(id), id);

        iter++;
    }
}

/**
 * ToString implemented using Iterators
 */
char const * MyId_AnotherToString(enum MY_ID literal)
{
    MY_ID_Iterator_t iter = MyId_IteratorBegin();
    MY_ID_Iterator_t end = MyId_IteratorEnd();

    while (iter != end)
    {
        if (MyId_IteratorToValue(iter) == literal)
        {
            return MY_ID_IMPL[iter].name;
        }
        iter++;
    }
}

/****************************************************************/
void ExtId_PrintAll(void)
{
    EXT_ID_Iterator_t iter;

    for (iter = ExtId_IteratorBegin();
         iter < ExtId_IteratorEnd();
         iter++)
    {
        enum EXT_ID id = ExtId_IteratorToValue(iter);
        printf("%s = %d\n", ExtId_ToString(id), id);
    }
}

/****************************************************************/
#define MINI_ID(_, _V) \
    _V(MINI_LEET, 1337) \

ENUM(MINI_ID);
ENUM_IMPL(MINI_ID);
ENUM_DEFINE_TOSTRING(MINI_ID, MiniId_ToString)

#define MICRO_ID(_, _V) \
    _(MICRO_LEET) \

ENUM(MICRO_ID);
/****************************************************************/

int main(void)
{
    ExtId_PrintAll();
    MyId_PrintAll();

    printf("%s = %d\n",
           MyId_AnotherToString(MY_ID_GROUP1_666),
           MY_ID_GROUP1_666);

    printf("%s = %d\n", MiniId_ToString(MINI_LEET), MINI_LEET);
    printf("%d\n", MICRO_LEET);
}

