#include "JonTest/TestSuite.h"
#include "JonTest/Assert.h"

#include <iostream>

TEST_SUITE(AssertFail)

TEST_CASE(jontest_fail_assertFail)
{
    std::cout << "EXPECT: AssertFail - jontest_fail_assertFail: case FAILED: jontest_fail_assertFail" << std::endl;
    assertFail("jontest_fail_assertFail");
}

TEST_CASE(expected_assertFail)
{
    expectedFailure(assertFail("protected assertFail"), "expected assertFail");
}

TEST_SUITE_END();