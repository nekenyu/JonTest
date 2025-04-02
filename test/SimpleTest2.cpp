#include "JonTest/TestSuite.h"

#include "JonTest/Assert.h"

#include <iostream>

TEST_SUITE(SimpleTest2)

    void setup()
    {
    }

    void teardown()
    {
    }

    TEST_CASE(a)
    {
        //std::cout << " a()";
        assert(true, "assert w/ true");
        assertTrue(true, "assertTrue w/ true");
        assertFalse(false, "assertFalse w/ false");
        const char* const p1 = nullptr;
        assertNullPtr(p1, "assertNullPtr w/ nullptr");
        const char* const p2 = "Hello, World!";
        assertValidPtr(p2, "assertValidPtr w/ valid");

        assertEqual(0, 0, "equal w/ 0 0");
        assertNotEqual(0, 1, "not equal w/ 0 0");
        assertLess(0, 1, "less w/ 0 1");
        assertLessEqual(0, 0, "less equal w/ 0 0");
        assertLessEqual(0, 1, "less equal w/ 0 1");
        assertGreater(1, 0, "greater  w/ 1 0");
        assertGreaterEqual(0, 0, "greater equal w/ 0 0");
        assertGreaterEqual(1, 0, "greater equal w/ 1 0");

        // Will fail
        assert(false, "assert w/ false");
        //assertTrue(false, "assertTrue w/ false");
        //assertFalse(true, "assertFalse w/ true");
        //assertNullPtr(p2, "assertNullPtr w/ valid");
        //assertValidPtr(p1, "assertValidPtr w/ nullptr");
    }
    
    TEST_CASE(b)
    {
        // Will fail
        assertLessEqual(1+1, 0, "less equal w/ 1+1 0");
    }

    TEST_CASE(c)
    {
        assertFail("Intentional Failure");
    }
    
TEST_SUITE_END();