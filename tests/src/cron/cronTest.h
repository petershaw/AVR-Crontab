#include "../../cu/cu.h"

#ifndef _cronTest_h
#define _cronTest_h

volatile int number;

// Declarations of tests
TEST(testCronInit);
TEST(testCronAdd);
TEST(testCronCount);
TEST(testCronRemove);
TEST(testCronClear);
TEST(testCronSorted);
TEST(testCronExecute);


// Collect tests into test suite
TEST_SUITE(CRON_TEST) {
    TEST_ADD(testCronInit),
    TEST_ADD(testCronAdd),
    TEST_ADD(testCronCount),
    TEST_ADD(testCronRemove),
    TEST_ADD(testCronClear),
    TEST_ADD(testCronSorted),
    TEST_ADD(testCronExecute),
    TEST_SUITE_CLOSURE
};

#endif
