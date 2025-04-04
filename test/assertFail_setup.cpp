#include "JonTest/TestSuite.h"
#include "JonTest/Assert.h"

#include <iostream>

TEST_SUITE(AssertFailSetup)

void setup()
{
    EXPECTED_FAILURE(assertFail("to be expected"), "expected failure)");

    std::cout << "EXPECT: AssertFailSetup - jontest_fail_assertFailSetup: setup FAILED: jontest_fail_assertFailSetup" << std::endl;
    assertFail("jontest_fail_assertFailSetup");
}

TEST_CASE(jontest_fail_assertFailSetup)
{
    assertFail("THIS SHOULD NEVER BE EXECUTED DUE TO FAILURE IN setup()");
}

TEST_SUITE_END();
