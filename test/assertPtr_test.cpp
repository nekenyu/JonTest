#include "JonTest/TestSuite.h"
#include "JonTest/Assert.h"

#include <iostream>

TEST_SUITE(AssertPtr)

TEST_CASE(assertNullPtr_test)
{
    assertNullPtr(nullptr, "nullptr should never fail");
    expectedFailure(assertNullPtr(this, "this should fail"), "verifies false failed");
}

TEST_CASE(assertValidPtr_test)
{
    assertValidPtr(this, "this should never fail");
    expectedFailure(assertValidPtr(nullptr, "nullptr should fail"), "verifies true failed");
}

TEST_SUITE_END();