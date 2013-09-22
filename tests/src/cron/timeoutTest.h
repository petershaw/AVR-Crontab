//
//
//

#ifndef _timeoutTest_h
#define _timeoutTest_h

#include "../../cu/cu.h"

int timeoutInvoked;

// Declarations of tests
TEST(testCronTimeoutAdd);
TEST(testCronTimeoutRemove);
TEST(testCronTimeoutExecute);


// Collect tests into test suite
TEST_SUITE(CRON_TIMEOUT_TEST) {
    TEST_ADD(testCronTimeoutAdd),
    TEST_ADD(testCronTimeoutRemove),
    TEST_ADD(testCronTimeoutExecute),
    TEST_SUITE_CLOSURE
};



#endif
