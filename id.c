/*
 * Enum property and iterator function examples.
 *
 * @author mark AT cognomen DOT co DOT uk
 *
 * @copyright Dedicated to the public domain. Use it as you wish.
 */
#include "enum.h"
#include "id.h"

#include <stdio.h>

/****************************************************************/

ENUM_IMPL(HEX);

ENUM_DEFINE_TOSTRING(HEX, Hex_ToString)

ENUM_DEFINE_ITERATOR(HEX,
                     Hex_IteratorBegin,
                     Hex_IteratorEnd,
                     Hex_IteratorToValue
                    )

