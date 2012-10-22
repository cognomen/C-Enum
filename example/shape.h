#ifndef SHAPE_H
#define SHAPE_H

#include "enum.h"

#define SHAPE(_, _V, _S, _VS) \
    _V(ANTI_LINE, -2) /* what bizarre kind of thing is this? */ \
    _V(POINT, 1) /* starts at 1 */ \
    _(LINE) /* auto increments to 2 */\
    _(TRIANGLE) \
    /* missing TETRAGON */ \
    _V(PENTAGON, 5) \
    /* missing HEXAGON */ \
    /* missing SEPTAGON */ \
    _V(OCTAGON, 8) \

/* Declare the ENUM */
ENUM(SHAPE);

/* Declare the Shape_ToString(enum SHAPE) function */
ENUM_DECLARE_TOSTRING(SHAPE, Shape_ToString);

#endif // SHAPE_H
