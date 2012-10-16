/*
 * Enum property and iterator function examples.
 *
 * @author mark AT cognomen DOT co DOT uk
 *
 * @copyright Dedicated to the public domain. Use it as you wish.
 */
#ifndef ID_H
#define ID_H

#include "enum.h"

#define HEX(_, _V) \
    _V(HEX_0, '0') \
    _(HEX_1) \
    _(HEX_2) \
    _(HEX_3) \
    _(HEX_4) \
    _(HEX_5) \
    _(HEX_6) \
    _(HEX_7) \
    _(HEX_8) \
    _(HEX_9) \
    _V(HEX_A, 'A') \
    _(HEX_B) \
    _(HEX_C) \
    _(HEX_D) \
    _(HEX_E) \
    _(HEX_F) \
    _V(HEX_MAX, HEX_F) \

ENUM(HEX);

ENUM_DECLARE_TOSTRING(HEX, Hex_ToString);
ENUM_DECLARE_ITERATOR(HEX,
                      Hex_IteratorBegin,
                      Hex_IteratorEnd,
                      Hex_IteratorToValue);

#endif  /* ID_H */

