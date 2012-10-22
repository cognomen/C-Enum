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
static char* test_Value(void)
{
    ENUM(VALUE);

    mu_assert("test_Value: Specified element not equal to 2",
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
static char* test_ValueNegative(void)
{
    ENUM(VALUE_NEGATIVE);

    mu_assert("test_ValueNegative: Specified element not equal to -2",
              VALUE_NEGATIVE_2 == -2);

    return 0;
}

/********************************/
#define VALUE_UNSIGNED(_, _V, _S, _VS) \
    _V(VALUE_UNSIGNED_2, 2u) \

/**
 * Ensure the specified unsigned value of a specified enum is correct.
 */
static char* test_ValueUnsigned(void)
{
    ENUM(VALUE_UNSIGNED);

    mu_assert("test_ValueUnsigned: Specified element not equal to 2u",
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
static char* test_ValueBitset(void)
{
    ENUM(VALUE_BITSET);

    mu_assert("test_ValueBitset: Specified element not equal to 2u",
              VALUE_BITSET_1 == 1u);
    mu_assert("test_ValueBitset: Specified element not equal to 2u",
              VALUE_BITSET_2 == 2u);
    mu_assert("test_ValueBitset: Specified element not equal to 2u",
              VALUE_BITSET_4 == 4u);
    mu_assert("test_ValueBitset: Specified element not equal to 2u",
              VALUE_BITSET_8 == 8u);
    mu_assert("test_ValueBitset: Specified element not equal to 2u",
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
static char* test_ValueInt(void)
{
    ENUM(VALUE_INT);

    mu_assert("test_ValueInt: Specified element not equal to INT_MIN",
              VALUE_INT_MIN == INT_MIN);
    mu_assert("test_ValueInt: Specified element not equal to INT_MAX",
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
static char* test_ValueLong(void)
{
    ENUM(VALUE_LONG);

    mu_assert("test_ValueLong: Specified element not equal to LONG_MIN",
              VALUE_LONG_MIN == LONG_MIN);
    mu_assert("test_ValueLong: Specified element not equal to LONG_MAX",
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
static char* test_ValueAbuse(void)
{
    ENUM(VALUE_ABUSE);

    mu_assert("test_ValueAbuse: 1 + 1 not equal to 2",
              VALUE_ABUSE_1_plus_1 == 2);
    mu_assert("test_ValueAbuse: 1 / 1 not equal to 1",
              VALUE_ABUSE_1_div_1 == 1);
    mu_assert("test_ValueAbuse: CHAR_A not equal to 'A'",
              VALUE_ABUSE_CHAR_A == 'A');
    mu_assert("test_ValueAbuse: Brackets element not equal to 5",
              VALUE_ABUSE_BRACKETS == 5);
    mu_assert("test_ValueAbuse: True element not equal to 'true'",
              VALUE_ABUSE_TRUE == 1);
    mu_assert("test_ValueAbuse: Recursive element not equal to 42",
              VALUE_ABUSE_RECURSIVE == 42);
    mu_assert("test_ValueAbuse: 1 + 1 not equal to 2",
              VALUE_ABUSE_1_plus_1 == 2);
    mu_assert("test_ValueAbuse: 'ENUM' element not equal to 10",
              VALUE_ABUSE_ENUM == 10);
    mu_assert("test_ValueAbuse: _ element not equal to 11",
              VALUE_ABUSE__ == 11);
    mu_assert("test_ValueAbuse: _V element not equal to 13",
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

#define VS(_, _V, _S, _VS) \
    _(VS_0) \
    _V(VS_1, 1) \
    _S(VS_2, "VS 2") \
    _VS(VS_4, 4, "VS 4") \
    _VS(VS_BUG, 4, "Bug") \

ENUM(VS);
ENUM_IMPL(VS);
ENUM_DEFINE_TOSTRING(VS, VS_ToString)

/**
 * Test ToString for each transform type. Test definition of two separate string functions.
 */
static char* test_ValueString(void)
{
    mu_assert("test_ValueString: ZEROTH element not equal to ZERO",
              VS_0 == 0);
    mu_assert("test_ValueString: ToString(VS_0) not equal to 'VS_0'",
              strcmp("VS_0", VS_ToString(VS_0)) == 0);

    mu_assert("test_ValueString: element VS_1 not equal to 1",
              VS_1 == 1);
    mu_assert("test_ValueString: ToString(VS_1) not equal to 'VS_1'",
              strcmp("VS_1", VS_ToString(VS_1)) == 0);

    mu_assert("test_ValueString: element VS_2 not equal to 2",
              VS_2 == 2);
    mu_assert("test_ValueString: ToString(VS_2) not equal to 'VS 2'",
              strcmp("VS 2", VS_ToString(VS_2)) == 0);

    mu_assert("test_ValueString: element VS_4 not equal to 4",
              VS_4 == 4);
    mu_assert("test_ValueString: ToString(VS_4) not equal to 'VS 4'",
              strcmp("VS 4", VS_ToString(VS_4)) == 0);

    return 0;
}

ENUM_DEFINE_TOSTRING(VS, VS_AnotherToString)

/**
 * Test equivalence of two separate string functions.
 */
static char* test_AnotherToString(void)
{
    mu_assert("test_AnotherToString: ToString(VS_4) not equal to 'ValueString 4'",
              strcmp(VS_ToString(VS_4), VS_AnotherToString(VS_4)) == 0);
}

/**
 * Test equivalence of two separate string functions.
 */
static char* test_Bug_1_ToStringLookup(void)
{
    mu_assert("test_Bug_1_ToStringLookup: ToString(VS_BUG) not equal to 'Bug'",
              strcmp("Bug", VS_ToString(VS_BUG)) == 0);
}

/********************************/
#define ITER(_, _V, _S, _VS) \
    _(ITER_0) \
    _V(ITER_1, 1) \
    _S(ITER_2, "ITER 2") \
    _VS(ITER_4, 4, "ITER 4") \
    _VS(ITER_8, 8, "ITER 8") \

ENUM(ITER);
ENUM_IMPL(ITER);
ENUM_DEFINE_TOSTRING(ITER, ITER_ToString)
ENUM_DEFINE_ITERATOR(ITER,
                     ITER_IteratorBegin,
                     ITER_IteratorEnd,
                     ITER_IteratorToValue)

/**
 * Ensure the first value of an auto enum is zero.
 */
static char* test_Iterator(void)
{
    struct test {
        const char* expected;
        char* error;
    } t[] = {
        {"ITER_0", "test_Iterator[ITER_0]: ITER_ToString failure"},
        {"ITER_1", "test_Iterator[ITER_1]: ITER_ToString failure"},
        {"ITER 2", "test_Iterator[ITER_2]: ITER_ToString failure"},
        {"ITER 4", "test_Iterator[ITER_4]: ITER_ToString failure"},
        {"ITER 8", "test_Iterator[ITER_8]: ITER_ToString failure"},
        {"ITER_BUG", "test_Iterator[BUG]: ITER_ToString failure"}
    };


    ITER_Iterator_t iter = ITER_IteratorBegin();
    ITER_Iterator_t end = ITER_IteratorEnd();

    while (iter <= end)
    {
        enum ITER id = ITER_IteratorToValue(iter);
        mu_assert(t[iter].error,
                  strcmp(ITER_ToString(id), t[iter].expected) == 0);


        iter++;
    }

    return 0;
}

/********************************/
char* test_enum(void)
{
    /*
     * ENUM tests
     */
    mu_run_test(test_AutoZero);
    /* Auto + Value tests */
    mu_run_test(test_Value);
    mu_run_test(test_CombinedValue);
    mu_run_test(test_DuplicateValue);
    mu_run_test(test_ReferencedValue);

    mu_run_test(test_ValueNegative);
    mu_run_test(test_ValueUnsigned);
    mu_run_test(test_ValueBitset);
    mu_run_test(test_ValueInt);
    mu_run_test(test_ValueLong);

    mu_run_test(test_NonMonotonic);
    mu_run_test(test_Discontinuity);

    //mu_run_test(test_ValueAbuse);

    mu_run_test(test_Coreferenced);

    /*
     * ENUM_IMPL tests
     */
    mu_run_test(test_ValueString);
    //mu_run_test(test_Bug_1_ToStringLookup);
    mu_run_test(test_Iterator);


    return 0;
}

