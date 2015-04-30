#ifndef UNITTEST_C_
#define UNITTEST_C_

#include <utils/UnitTest.h>

int sss_tests_run = 0;

char* sss_assert(char* msg, int test) {
    if(!(test))
        return msg;
    return 0;
}

char* sss_refute(char* msg, int test) {
    if(test)
        return msg;
    return 0;
}

char* sss_run_test(char* (*fptr)()) {
    char* msg = fptr();
    sss_tests_run++;
    if(msg) return msg;
    return 0;
}

#endif /* UNITTEST_C_ */
