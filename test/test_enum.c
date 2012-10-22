/*
 * Tests enum macros.
 */

#include "minunit.h"
#include <stdint.h>
#include <string.h> /* memset, memcmp */
#include <limits.h>
#include <stdbool.h>

#include "enum.h"


char* test_enum(void);

/***********************************
 * ENUM Declaration tests
 ***********************************/

/********************************/
#define AUTO(_, _V, _S, _VS) \
    _(AUTO_ZERO) \

/**
 * Ensure the first value of an auto enum is zero.
 */
static char* test_AutoZero(void)
{
    ENUM(AUTO);

    mu_assert("test_AutoZero: ZEROTH element not equal to ZERO",
              AUTO_ZERO == 0);

    return 0;
}

/********************************/
#define VALUE(_, _V, _S, _VS) \
    _V(VALUE_2, 2) \

/**
 * Ensure the specified value of a specified enum is correct.
 */
static char* test_SpecifiedValue(void)
{
    ENUM(VALUE);

    mu_assert("test_SpecifiedValue: Specified element not equal to 2",
              VALUE_2 == 2);

    return 0;
}

/********************************/
#define COMBINED(_, _V, _S, _VS) \
    _V(COMBINED_3, 3) \
    _(COMBINED_4) \

/**
 * Ensure an auto value following a specified value is correct.
 */
static char* test_CombinedValue(void)
{
    ENUM(COMBINED);

    mu_assert("test_CombinedValue: Specified element not equal to 3",
              COMBINED_3 == 3);
    mu_assert("test_CombinedValue: Subsequent element not equal to 4",
              COMBINED_4 == 4);

    return 0;
}

/********************************/
#define DUPLICATE(_, _V, _S, _VS) \
    _V(DUPLICATE_3A, 3) \
    _V(DUPLICATE_3B, 3) \

/**
 * Ensure enum elements can share the same value.
 */
static char* test_DuplicateValue(void)
{
    ENUM(DUPLICATE);

    mu_assert("test_DuplicateValue: Specified element not equal to 3",
              DUPLICATE_3A == 3);
    mu_assert("test_DuplicateValue: Subsequent element not equal to 3",
              DUPLICATE_3B == 3);

    return 0;
}

/********************************/
#define REFERENCED(_, _V, _S, _VS) \
    _V(REFERENCED_A, 3) \
    _V(REFERENCED_B, REFERENCED_A) \
    _V(REFERENCED_C, REFERENCED_A + REFERENCED_B) \

/**
 * Ensure a specified value referencing a previous specified value is valid.
 */
static char* test_ReferencedValue(void)
{
    ENUM(REFERENCED);

    mu_assert("test_ReferencedValue: Specified element not equal to 3",
              REFERENCED_A == 3);
    mu_assert("test_ReferencedValue: Refering element not equal to referee",
              REFERENCED_B == 3);
    mu_assert("test_ReferencedValue: Refering element not equal to referee",
              REFERENCED_C == 6);

    return 0;
}

/********************************/
#define VALUE_NEGATIVE(_, _V, _S, _VS) \
    _V(VALUE_NEGATIVE_2, -2) \

/**
 * Ensure the specified negative value of a specified enum is correct.
 */
static char* test_SpecifiedNegative(void)
{
    ENUM(VALUE_NEGATIVE);

    mu_assert("test_SpecifiedNegative: Specified element not equal to -2",
              VALUE_NEGATIVE_2 == -2);

    return 0;
}

/********************************/
#define VALUE_UNSIGNED(_, _V, _S, _VS) \
    _V(VALUE_UNSIGNED_2, 2u) \

/**
 * Ensure the specified unsigned value of a specified enum is correct.
 */
static char* test_SpecifiedUnsigned(void)
{
    ENUM(VALUE_UNSIGNED);

    mu_assert("test_SpecifiedUnsigned: Specified element not equal to 2u",
              VALUE_UNSIGNED_2 == 2u);

    return 0;
}

/********************************/
#define VALUE_BITSET(_, _V, _S, _VS) \
    _V(VALUE_BITSET_1, (1u << 0)) \
    _V(VALUE_BITSET_2, (1u << 1)) \
    _V(VALUE_BITSET_4, (1u << 2)) \
    _V(VALUE_BITSET_8, (1u << 3)) \
    _V(VALUE_BITSET_16, (1u << 4)) \

/**
 * Ensure the specified unsigned value of a specified enum is correct.
 */
static char* test_SpecifiedBitset(void)
{
    ENUM(VALUE_BITSET);

    mu_assert("test_SpecifiedBitset: Specified element not equal to 2u",
              VALUE_BITSET_1 == 1u);
    mu_assert("test_SpecifiedBitset: Specified element not equal to 2u",
              VALUE_BITSET_2 == 2u);
    mu_assert("test_SpecifiedBitset: Specified element not equal to 2u",
              VALUE_BITSET_4 == 4u);
    mu_assert("test_SpecifiedBitset: Specified element not equal to 2u",
              VALUE_BITSET_8 == 8u);
    mu_assert("test_SpecifiedBitset: Specified element not equal to 2u",
              VALUE_BITSET_16 == 16u);

    return 0;
}

/********************************/
#define VALUE_INT(_, _V, _S, _VS) \
    _V(VALUE_INT_MIN, INT_MIN) \
    _V(VALUE_INT_MAX, INT_MAX) \

/**
 * Ensure the specified unsigned value of a specified enum is correct.
 */
static char* test_SpecifiedInt(void)
{
    ENUM(VALUE_INT);

    mu_assert("test_SpecifiedInt: Specified element not equal to INT_MIN",
              VALUE_INT_MIN == INT_MIN);
    mu_assert("test_SpecifiedInt: Specified element not equal to INT_MAX",
              VALUE_INT_MAX == INT_MAX);

    return 0;
}

/********************************/
#define VALUE_LONG(_, _V, _S, _VS) \
    _V(VALUE_LONG_MIN, LONG_MIN) \
    _V(VALUE_LONG_MAX, LONG_MAX) \

/**
 * Ensure the specified unsigned value of a specified enum is correct.
 */
static char* test_SpecifiedLong(void)
{
    ENUM(VALUE_LONG);

    mu_assert("test_SpecifiedLong: Specified element not equal to LONG_MIN",
              VALUE_LONG_MIN == LONG_MIN);
    mu_assert("test_SpecifiedLong: Specified element not equal to LONG_MAX",
              VALUE_LONG_MAX == LONG_MAX);

    return 0;
}

/********************************/
#define NON_MONOTONIC(_, _V, _S, _VS) \
    _V(NON_MONOTONIC_2, 2) \
    _V(NON_MONOTONIC_1, 1) \
    _V(NON_MONOTONIC_0, 0) \
    _V(NON_MONOTONIC_MINUS_1, -1) \

/**
 * Ensure a specified enum value, less than its predecessor, is correct.
 */
static char* test_NonMonotonic(void)
{
    ENUM(NON_MONOTONIC);

    mu_assert("test_NonMonotonic: Specified element not equal to 2",
              NON_MONOTONIC_2 == 2);
    mu_assert("test_NonMonotonic: Subsequent element not equal to 1",
              NON_MONOTONIC_1 == 1);
    mu_assert("test_NonMonotonic: Subsequent element not equal to 0",
              NON_MONOTONIC_0 == 0);
    mu_assert("test_NonMonotonic: Subsequent element not equal to -1",
              NON_MONOTONIC_MINUS_1 == -1);

    return 0;
}

/********************************/
#define DISCONTINUITY(_, _V, _S, _VS) \
    _V(DISCONTINUITY_5, 5) \
    _(DISCONTINUITY_6) \
    _V(DISCONTINUITY_8, 8) \
    _(DISCONTINUITY_9) \

/**
 * Ensure an enum with a discontinuity is correct.
 */
static char* test_Discontinuity(void)
{
    ENUM(DISCONTINUITY);

    mu_assert("test_Discontinuity: Specified element not equal to 5",
              DISCONTINUITY_5 == 5);

    mu_assert("test_Discontinuity: Subsequent element not equal to 6",
              DISCONTINUITY_6 == 6);

    mu_assert("test_Discontinuity: Specified element not equal to 8",
              DISCONTINUITY_8 == 8);

    mu_assert("test_Discontinuity: Subsequent element not equal to 9",
              DISCONTINUITY_9 == 9);

    return 0;
}

/********************************/
#if 0
#define VALUE_ABUSE(_, _V, _S, _VS) \
    _V(VALUE_ABUSE_1_plus_1, 1 + 1) \
    _V(VALUE_ABUSE_1_div_1, 1 / 1) \
    _V(VALUE_ABUSE_CHAR_A, 'A') \
    _V(VALUE_ABUSE_BRACKETS, ((5)) ) \
    _V(VALUE_ABUSE_TRUE, true) \
    _V(VALUE_ABUSE, 42) \
    _V(VALUE_ABUSE_RECURSIVE, VALUE_ABUSE) \
    /* The following break later usage */ \
    _V(ENUM, 10) \
    _V(ENUM_AS_ENUM, 11) \
    _V(ENUM_AS_ENUM_VALUE, 13) \
    _V(VALUE_ABUSE_ENUM, ENUM) \
    _V(VALUE_ABUSE__, _) \
    _V(VALUE_ABUSE__V, _V, _S, _VS) \

/**
 * Ensure ENUM is resilient to declaration abuse.
 */
static char* test_SpecifiedAbuse(void)
{
    ENUM(VALUE_ABUSE);

    mu_assert("test_SpecifiedAbuse: 1 + 1 not equal to 2",
              VALUE_ABUSE_1_plus_1 == 2);
    mu_assert("test_SpecifiedAbuse: 1 / 1 not equal to 1",
              VALUE_ABUSE_1_div_1 == 1);
    mu_assert("test_SpecifiedAbuse: CHAR_A not equal to 'A'",
              VALUE_ABUSE_CHAR_A == 'A');
    mu_assert("test_SpecifiedAbuse: Brackets element not equal to 5",
              VALUE_ABUSE_BRACKETS == 5);
    mu_assert("test_SpecifiedAbuse: True element not equal to 'true'",
              VALUE_ABUSE_TRUE == 1);
    mu_assert("test_SpecifiedAbuse: Recursive element not equal to 42",
              VALUE_ABUSE_RECURSIVE == 42);
    mu_assert("test_SpecifiedAbuse: 1 + 1 not equal to 2",
              VALUE_ABUSE_1_plus_1 == 2);
    mu_assert("test_SpecifiedAbuse: 'ENUM' element not equal to 10",
              VALUE_ABUSE_ENUM == 10);
    mu_assert("test_SpecifiedAbuse: _ element not equal to 11",
              VALUE_ABUSE__ == 11);
    mu_assert("test_SpecifiedAbuse: _V element not equal to 13",
              VALUE_ABUSE__V == 13);

    return 0;
}
#endif

/********************************/
#define COREFERENCED_A(_, _V, _S, _VS) \
    _V(COREFERENCED_A1, 1) \

#define COREFERENCED_B(_, _V, _S, _VS) \
    _V(COREFERENCED_B1, COREFERENCED_A1) \

static char* test_Coreferenced(void)
{
    ENUM(COREFERENCED_A);
    ENUM(COREFERENCED_B);

    mu_assert("test_Coreferenced: Element A1 not equal to Element B1",
              COREFERENCED_A1 == COREFERENCED_B1);

    return 0;
}


/***********************************
 * ENUM_IMPL tests
 ***********************************/
ENUM(AUTO);
ENUM_IMPL(AUTO);
ENUM_DECLARE_TOSTRING(AUTO, Auto_ToString);
ENUM_DEFINE_TOSTRING(AUTO, Auto_ToString)

/**
 * Ensure the first value of an auto enum is zero.
 */
static char* test_ImplAutoZero(void)
{
    ENUM(AUTO);

    mu_assert("test_AutoZero: ZEROTH element not equal to ZERO",
              strcmp("AUTO_ZERO", Auto_ToString(AUTO_ZERO)) == 0);

    return 0;
}

/********************************/
#define QUAD(_, _V, _S, _VS) \
    _(QUAD_0) \
    _V(QUAD_1, 1) \
    _S(QUAD_2, "Quad 2") \
    _VS(QUAD_4, 4, "Quad 4") \

ENUM(QUAD);
ENUM_IMPL(QUAD);
ENUM_DEFINE_TOSTRING(QUAD, Quad_ToString)
ENUM_DEFINE_TOSTRING(QUAD, Quad_AnotherToString)

/**
 * Ensure the first value of an auto enum is zero.
 */
static char* test_Quad(void)
{
    mu_assert("test_Quad: ZEROTH element not equal to ZERO",
              QUAD_0 == 0);

    mu_assert("test_Quad: element QUAD_1 not equal to 1",
              QUAD_1 == 1);

    mu_assert("test_Quad: element QUAD_2 not equal to 2",
              QUAD_2 == 2);
    mu_assert("test_Quad: ToString(QUAD_2) not equal to 'Quad 2'",
              strcmp("Quad 2", Quad_ToString(QUAD_2)) == 0);

    mu_assert("test_Quad: element QUAD_4 not equal to 4",
              QUAD_4 == 4);
    mu_assert("test_Quad: ToString(QUAD_4) not equal to 'Quad 4'",
              strcmp("Quad 4", Quad_ToString(QUAD_4)) == 0);
    mu_assert("test_Quad: ToString(QUAD_4) not equal to 'Quad 4'",
              strcmp("Quad 4", Quad_AnotherToString(QUAD_4)) == 0);


    return 0;
}

/********************************/
char* test_enum(void)
{
    mu_run_test(test_AutoZero);
    mu_run_test(test_SpecifiedValue);
    mu_run_test(test_CombinedValue);
    mu_run_test(test_DuplicateValue);
    mu_run_test(test_ReferencedValue);

    mu_run_test(test_SpecifiedNegative);
    mu_run_test(test_SpecifiedUnsigned);
    mu_run_test(test_SpecifiedBitset);
    mu_run_test(test_SpecifiedInt);
    mu_run_test(test_SpecifiedLong);

    mu_run_test(test_NonMonotonic);
    mu_run_test(test_Discontinuity);

    //mu_run_test(test_SpecifiedAbuse);

    mu_run_test(test_Coreferenced);

    mu_run_test(test_ImplAutoZero);
    mu_run_test(test_Quad);

    return 0;
}

