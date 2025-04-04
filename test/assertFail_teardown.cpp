#include "JonTest/TestSuite.h"
#include "JonTest/Assert.h"

#include <iostream>

TEST_SUITE(AssertFailTeardown)

void teardown()
{
    EXPECTED_FAILURE(assertFail("to be expected"), "expected failure)");

    std::cout << "EXPECT: AssertFailTeardown - jontest_fail_assertFailTeardown: teardown FAILED: jontest_fail_assertFailTeardown" << std::endl;
    assertFail("jontest_fail_assertFailTeardown");
}

TEST_CASE(jontest_fail_assertFailTeardown)
{
    // Nothing to do, must pass and fail in teardown
}

TEST_SUITE_END();
