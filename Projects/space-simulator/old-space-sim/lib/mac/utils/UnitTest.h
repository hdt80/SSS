#ifdef __cplusplus
extern "C" {
#endif

// #define sss_assert(msg, test) do { if(!(test)) return msg; } while(0)
// #define sss_refute(msg, test) do { if(test) return msg; } while(0)
// #define sss_run_test(test) do { char* message = test(); tests_run++; \
//                             if (message) return message; } while(0)
//

const char* sss_assert(const char* msg, int test);
const char* sss_refute(const char* msg, int test);
const char* sss_run_test(const char* (*fptr)());

extern int sss_tests_run;

#ifdef __cplusplus
};
#endif
