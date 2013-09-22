// Include definition of test suites
#ifndef IGNOREINTESTS
#define IGNOREINTESTS 1
#endif

#include "cron/cronTest.h"
#include "cron/timerTest.h"
#include "cron/timeoutTest.h"

void *dummy(void);

// This struct contains all test suites
TEST_SUITES {
    TEST_SUITE_ADD(CRON_TEST),      // add CRON test suite
    TEST_SUITE_ADD(TIMER_TEST),     // add TIMER test suite
    TEST_SUITE_ADD(CRON_TIMEOUT_TEST), // add TIMEOUT test suite
    TEST_SUITES_CLOSURE
};

int main(int argc, char *argv[]) {
    // Set up directory where are stored files with outputs from test
    // suites
    CU_SET_OUT_PREFIX("regressions/");
    
    // Run all test suites
    CU_RUN(argc, argv);
    
    return 0;
}
