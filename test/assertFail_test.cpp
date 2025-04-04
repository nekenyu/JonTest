#include "JonTest/TestSuite.h"
#include "JonTest/Assert.h"

TEST_SUITE(AssertFail)

TEST_CASE(jontest_fail_assertFail)
{
    // This WILL fail the test to demonstrate feature, and will be monitored externally
    assertFail("jontest_fail_assertFail");
}

TEST_CASE(expected_assertFail)
{
    EXPECTED_FAILURE(assertFail("protected assertFail"), "expected assertFail");
}

TEST_SUITE_END();