#include "enum.h"
#include "id.h"

#ifndef PREPROCESS
#   include <stdio.h>
#endif

/****************************************************************/

ENUM_IMPL(EXT_ID);
    ENUM_DEFINE_TOSTRING(EXT_ID, ExtId_ToString)
    ENUM_DEFINE_ITERATOR(EXT_ID,
                         ExtId_IteratorBegin,
                         ExtId_IteratorEnd,
                         ExtId_IteratorToValue
                        )

