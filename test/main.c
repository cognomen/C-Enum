/**
 * Main function for unit tests to link against.
 *
 * Author: mark AT cognomen DOT co DOT uk
 * Dedicated to the public domain. Use it as you wish.
 */
#if defined UNIT_TEST

#include <stdio.h>

char* UNIT_TEST(void);

int main(int arcg, char** argv)
{
    // UNIT_TEST set to test function in Makefile
    char* result = UNIT_TEST();

    if (result) {
        printf("FAILED: %s: %s\n", argv[0], result);
        return 1;
    }

    printf("PASSED: %s\n", argv[0]);
    return 0;
}
#endif


