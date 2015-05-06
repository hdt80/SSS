#ifndef UNITTEST_C_
#define UNITTEST_C_

#include <utils/UnitTest.h>

int sss_tests_run = 0;

const char* sss_assert(const char* msg, int test) {
    if(!(test))
        return msg;
    return 0;
}

const char* sss_refute(const char* msg, int test) {
    if(test)
        return msg;
    return 0;
}

const char* sss_run_test(const char* (*fptr)()) {
    const char* msg = fptr();
    sss_tests_run++;
    if(msg) return msg;
    return 0;
}

#endif /* UNITTEST_C_ */
