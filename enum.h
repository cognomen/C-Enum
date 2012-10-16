/**
 * Implementation of enum property and iterator functions.
 *
 * @author mark AT cognomen DOT co DOT uk
 *
 * @copyright Dedicated to the public domain. Use it as you wish.
 */

/**
 * @defgroup Enum
 * 
 * @brief Module for generating enum property and iterator functions.
 *
 * Enum uses parameterized X-macros to expand a list of enum entry macros into
 * various C constructs.
 *
 * Ordinary enums, a table of enum value strings, an EnumToString function and 
 * enum iterator functions can all be generated.
 *
 * Enum supports generating separate code for interface and implementation.
 */

/**
 * @addtogroup Enum
 * @{
 */

/**
 * @file
 *
 * @brief Defines X-Macros for generating enum properties and iterators.
 *
 */
#ifndef ENUM_H
#define ENUM_H

#include <stddef.h> // size_t

/**
 * Declares an enum @p e.
 *
 * A parameterized X-Macro. It accepts a list of macro instances
 * which are expanded via one of two applied X-macros.
 *
 * @param e A space-separated list of @ref ENUM_AS_ENUM or @ref ENUM_AS_ENUM_VALUE tuples
 *
 * @code
 * #define SHAPE_POINTS(_, _V) \
 *     _V(POINT, 1) \
 *     _(LINE) \
 *     _(TRIANGLE) \
 *     _(TETRAGON) \
 *     _(PENTAGON) \
 *     _V(OCTAGON, 8)
 *
 * ENUM(SHAPE_POINTS);
 * 
 * enum SHAPE_POINTS points = TETRAGON;
 *
 * switch (points)
 * {
 *     case TRIANGLE:
 *         printf("A Triangle\n");
 *         break;
 *     case TETRAGON:
 *         printf("A Tetragon\n");
 *         break;
 *     default:
 *         printf("Unknown Shape");
 * }
 * @endcode
 *
 */
#define ENUM(e) \
    enum e { \
        e(ENUM_AS_ENUM, ENUM_AS_ENUM_VALUE) \
    } \

/**
 * Allocates data table for the enum @p e.
 *
 * A parameterized X-Macro. It accepts a list of macro instances
 * which are expanded via one of two applied X-macros.
 *
 * It emits @p e_IMPL, a static constant array of ("name", value)
 * pairs.
 *
 * @param e A space-separated list of @ref ENUM_AS_NAME or @ref ENUM_AS_NAME_VALUE tuples
 *
 * @note This is a required pre-declaration for all ENUM_DEFINE_* macros.
 *
 * @code
 * ENUM_IMPL(SHAPE_POINTS);
 * @endcode
 *
 */
#define ENUM_IMPL(e) \
    static const struct e##_PropertiesEntry\
    {\
        char const* name;\
        enum e      value;\
    } e##_IMPL[] = \
    { \
        e(ENUM_AS_NAME, ENUM_AS_NAME_VALUE) \
    }

/**
 * Emit a ToString function declaration @p fname for the enum @p e.
 */
#define ENUM_DECLARE_TOSTRING(e, fname) \
        char const * fname(enum e literal)

/**
 * Emit a ToString function definition @p fname for the enum @p e.
 *
 * @param e An enum name.
 * @param fname of ToString function.
 *
 * @pre @ref ENUM_IMPL declaration must be visible in the context.
 *
 * @note No closing semi-colon.
 * @bug If a multiple enum entries have the same constant value, the name of the first one will be printed.
 *
 * @code
 * ENUM_IMPL(SHAPE_POINTS);
 * ...
 * ENUM_DEFINE_TOSTRING(SHAPE_POINTS, Shape_ToString)
 *
 * printf("A %s has %d sides.\n", Shape_ToString(TETRAGON), TETRAGON);
 * @endcode
 *
 */
#define ENUM_DEFINE_TOSTRING(e, fname) \
    ENUM_DECLARE_TOSTRING(e, fname) \
    { \
        size_t idx = 0; \
        \
        for (idx = 0; idx < sizeof(e##_IMPL)/sizeof(*e##_IMPL); ++idx) \
        { \
            if ((literal) == e##_IMPL[idx].value) \
            { \
                return e##_IMPL[idx].name; \
            } \
        } \
        \
        return "ERROR: UNKNOWN ENUM TYPE"; \
    } \

/*************************************************************************
 * Iterators
 *************************************************************************/
/**
 * Emit iterator function declarations for enum @p e.
 *
 * @param e       Enum Name.
 * @param begin   Iterator Begin function name.
 * @param end     Iterator End function name.
 * @param tovalue Iterator to Enum value function name.
 *
 * @code
 * ENUM_DECLARE_ITERATOR(SHAPE_POINTS,
 *                       Shape_IteratorBegin,
 *                       Shape_IteratorEnd,
 *                       Shape_IteratorToValue);
 * @endcode
 *
 */
/* Note it is critical that the iterator type be a signed type
 * so that &lt; tests against Begin() do not fail.
 */
#define ENUM_DECLARE_ITERATOR(e, begin, end, tovalue) \
    typedef int e##_Iterator_t; \
    e##_Iterator_t begin(void); \
    e##_Iterator_t end(void); \
    enum e tovalue(e##_Iterator_t iter) \

/**
 * Emit iterator function definitions for enum @p e.
 *
 * @param e       Enum Name.
 * @param begin   Iterator Begin function name.
 * @param end     Iterator End function name.
 * @param tovalue Iterator to Enum value function name.
 *
 * @note No closing semi-colon.
 * @pre @ref ENUM_IMPL declaration must be visible in the context.
 *
 * @code
 * ENUM_IMPL(SHAPE_POINTS);
 * ...
 * ENUM_DEFINE_ITERATOR(SHAPE_POINTS,
 *                      Shape_IteratorBegin,
 *                      Shape_IteratorEnd,
 *                      Shape_IteratorToValue)
 *
 * void Shape_PrintAll(void)
 * {
 *     SHAPE_POINTS_Iterator_t iter = Shape_IteratorBegin();
 *     SHAPE_POINTS_Iterator_t end = Shape_IteratorEnd();
 *
 *     while (iter <= end)
 *     {
 *         enum SHAPE_POINTS id = Shape_IteratorToValue(iter);
 *         printf("A %s has %d sides.\n", Shape_ToString(id), id);
 *
 *         iter++;
 *     }
 * }
 * @endcode
 *
 */
#define ENUM_DEFINE_ITERATOR(e, begin, end, tovalue) \
    e##_Iterator_t begin(void) \
    { \
        return (e##_Iterator_t) 0; \
    } \
    \
    e##_Iterator_t end(void) \
    { \
        return sizeof(e##_IMPL)/sizeof(*e##_IMPL) - 1; \
    } \
    \
    enum e tovalue(e##_Iterator_t iter) \
    { \
        return e##_IMPL[iter].value; \
    } \

/*************************************************************************
 * Internal macros
 *************************************************************************/
/**
 *     @addtogroup Internal
 *     @{
 */


/**
 * Internal X-Macro which emits an enum entry as @p name only with an implicit
 * enum value.
 *
 * @param name An enum entry name
 *
 * @code
 * ENUM_AS_ENUM(SIDES_OF_A_TRIANGLE) => SIDES_OF_A_TRIANGLE,
 * @endcode
 */
#define ENUM_AS_ENUM(name) name ,

/**
 * Internal X-Macro which emits an enum entry as @p name and @p value.
 *
 * @param name An enum entry name
 * @param value The constant-value assigned to the enum entry name
 *
 * @code
 * ENUM_AS_ENUM_VALUE(SIDES_OF_A_TRIANGLE, 3) => SIDES_OF_A_TRIANGLE = 3,
 * @endcode
 */
#define ENUM_AS_ENUM_VALUE(name, value) name = value,

/**
 * Internal X-Macro which emits a (@p "name", @p (name)) array initializer tuple.
 *
 * @param name An enum entry name
 *
 * @code
 * ENUM_AS_NAME(SIDES_OF_A_TRIANGLE) => {"SIDES_OF_A_TRIANGLE", (SIDES_OF_A_TRIANGLE)},
 * @endcode
 */
#define ENUM_AS_NAME(name)       {#name, (name)},

/**
 * Internal X-Macro which emits a (@p "name", @p value) array initializer tuple.
 *
 * @param name An enum entry name
 * @param value The constant-value assigned to the enum entry name
 *
 * @code
 * ENUM_AS_NAME_VALUE(SIDES_OF_A_TRIANGLE, 3) => {"SIDES_OF_A_TRIANGLE", (3)},
 * @endcode
 */
#define ENUM_AS_NAME_VALUE(name, value) {#name, (int) value},

/**
 *     @} // addtogroup Internal
 */

#endif /* ENUM_H */

/**
 * @} // addtogroup Enum
 */

