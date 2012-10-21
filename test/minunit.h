/*
 *      Minimalist unit test macros
 *
 *   Derived from MinUnit
 *     http://www.jera.com/techinfo/jtns/jtn002.html
 *   Released under a public domain licence
 *     http://www.jera.com/techinfo/jtns/jtn002.html#License
 *
 */

#define mu_assert(message, test) do { if (!(test)) {return message;} } while (0)
#define mu_run_test(test) do { char *message = test(); \
                                if (message) {return message;} } while (0)

