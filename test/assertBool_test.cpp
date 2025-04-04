#include "JonTest/TestSuite.h"
#include "JonTest/Assert.h"

#include <iostream>

TEST_SUITE(AssertBool)

TEST_CASE(assert_test)
{
    assert(true, "true should never fail");
    EXPECTED_FAILURE(assert(false, "False should fail"), "verifies false failed");
}

TEST_CASE(assertTrue_test)
{
    assertTrue(true, "true should never fail");
    EXPECTED_FAILURE(assertTrue(false, "False should fail"), "verifies false failed");
}

TEST_CASE(assertFalse_test)
{
    assertFalse(false, "false should never fail");
    EXPECTED_FAILURE(assertFalse(true, "true should fail"), "verifies true failed");
}

TEST_SUITE_END();