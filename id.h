#ifndef ID_H
#define ID_H

#include "enum.h"

#define EXT_ID(_, _V) \
    _V(EXT_ID_0, 0) \
    _(EXT_ID_GROUP1_START) \
    _V(EXT_ID_GROUP1_0, EXT_ID_GROUP1_START) \
    _(EXT_ID_GROUP1_1) \
    _(EXT_ID_GROUP1_2) \
    _(EXT_ID_GROUP1_3) \
    _V(EXT_ID_GROUP1_666, 666) \
    _(EXT_ID_MAX) \

ENUM(EXT_ID);

ENUM_DECLARE_TOSTRING(EXT_ID, ExtId_ToString);
ENUM_DECLARE_ITERATOR(EXT_ID,
                      ExtId_IteratorBegin,
                      ExtId_IteratorEnd,
                      ExtId_IteratorToValue);

#endif  /* ID_H */

