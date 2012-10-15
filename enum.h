#ifndef ENUM_H
#define ENUM_H

#ifndef PREPROCESS
#   include <stdlib.h>
#endif

/*
 * Internal macros
 */
#define ENUM_AS_ENUM(name) name ,
#define ENUM_AS_ENUM_VALUE(name, value) name = value,

#define ENUM_AS_NAME(name)       {#name, (name)},
#define ENUM_AS_NAME_VALUE(name, value) {#name, value},

/**
 * Declares an enum @p e.
 */
#define ENUM(e) \
    enum e { \
        e(ENUM_AS_ENUM, ENUM_AS_ENUM_VALUE) \
    } \

/**
 * Allocates data table for the enum @p e.
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
 * @pre ENUM_IMPL declaration must be visible in the context.
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

/**
 * Emit iterator function declarations for enum @p e.
 *
 * Declares the following functions:
 * @code
 *     e_Iterator_t begin(void);
 *     e_Iterator_t end(void);
 *     enum e       tovalue(e_Iterator_t)
 * @endcode
 *
 * @param e       Enum Name.
 * @param begin   Iterator Begin function name.
 * @param end     Iterator End function name.
 * @param tovalue Iterator to Enum value function name.
 */
#define ENUM_DECLARE_ITERATOR(e, begin, end, tovalue) \
    typedef size_t e##_Iterator_t; \
    e##_Iterator_t begin(void); \
    e##_Iterator_t end(void); \
    enum e tovalue(e##_Iterator_t iter) \

/**
 * Emit iterator function definitions for enum @p e.
 *
 * Defines the following functions:
 * @code
 *     e_Iterator_t begin(void) {...}
 *     e_Iterator_t end(void) {...}
 *     enum e       tovalue(e_Iterator_t) {...}
 * @endcode
 *
 * @param e       Enum Name.
 * @param begin   Iterator Begin function name.
 * @param end     Iterator End function name.
 * @param tovalue Iterator to Enum value function name.
 *
 * @pre ENUM_IMPL declaration must be visible in the context.
 */
#define ENUM_DEFINE_ITERATOR(e, begin, end, tovalue) \
    e##_Iterator_t begin(void) \
    { \
        return (e##_Iterator_t) 0; \
    } \
    \
    e##_Iterator_t end(void) \
    { \
        return sizeof(e##_IMPL)/sizeof(*e##_IMPL); \
    } \
    \
    enum e tovalue(e##_Iterator_t iter) \
    { \
        return e##_IMPL[iter].value; \
    } \


#endif /* ENUM_H */
