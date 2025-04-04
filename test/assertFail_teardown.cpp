#include "JonTest/TestSuite.h"
#include "JonTest/Assert.h"

TEST_SUITE(AssertFailTeardown)

void teardown()
{
    EXPECTED_FAILURE(assertFail("to be expected"), "expected failure)");

    // This WILL fail the test to demonstrate feature, and will be monitored externally
    assertFail("jontest_fail_assertFailTeardown");
}

TEST_CASE(jontest_fail_assertFailTeardown)
{
    // Nothing to do, must pass and fail in teardown
}

TEST_SUITE_END();
