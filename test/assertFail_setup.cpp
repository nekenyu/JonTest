#include "JonTest/TestSuite.h"
#include "JonTest/Assert.h"

TEST_SUITE(AssertFailSetup)

void setup()
{
    EXPECTED_FAILURE(assertFail("to be expected"), "expected failure)");

    // This WILL fail the test to demonstrate feature, and will be monitored externally
    assertFail("jontest_fail_assertFailSetup");
}

TEST_CASE(jontest_fail_assertFailSetup)
{
    assertFail("THIS SHOULD NEVER BE EXECUTED DUE TO FAILURE IN setup()");
}

TEST_SUITE_END();
