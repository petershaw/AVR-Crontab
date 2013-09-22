#include "../../cu/cu.h"

#ifndef _timerTest_h
#define _timerTest_h

// Declarations of tests
TEST(testTimerInit);
TEST(testTimerTick);
TEST(testTimerOverclock);
TEST(testTimerGetTime);
TEST(testTimerSecondsNotOver);

// Collect tests into test suite
TEST_SUITE(TIMER_TEST) {
    TEST_ADD(testTimerInit),
    TEST_ADD(testTimerTick),
    TEST_ADD(testTimerOverclock),
    TEST_ADD(testTimerGetTime),
    TEST_ADD(testTimerSecondsNotOver),
    TEST_SUITE_CLOSURE
};

#endif
