#include "JonTest/TestSuite.h"
#include "JonTest/Assert.h"

#include <iostream>

/** Example execution of JonTest showing a number of asserts and test cases.
 */
int /// \returns unix return code where 0 is success, positive values are the number of failed tests
main(
    int argc, ///< Number of arguments to program
    char**argv///< array of argc argument char* values to program
)
{
    JonTest::StreamLogger logger(std::cout, true);
    const JonTest::Count counts = JonTest::TestRunner::get().run(logger);
    return counts.fails;
}

TEST_SUITE(SimpleTest)

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

        assertException(throw 42, int, "Validate assertException");

        // Will fail
        assert(false, "assert w/ false");
        //assertTrue(false, "assertTrue w/ false");
        //assertFalse(true, "assertFalse w/ true");
        //assertNullPtr(p2, "assertNullPtr w/ valid");
        //assertValidPtr(p1, "assertValidPtr w/ nullptr");
    }
    
    TEST_CASE(b)
    {
        // Demonstrate we can expect a failure of an assert
        EXPECTED_FAILURE(assertLessEqual(2+1, 0, "less equal w/ 2+1 0"), "Validates expected failure");
        EXPECTED_FAILURE(assertLessEqual(1+1, 0, "less equal w/ 1+1 0"), "Validates expected failure");

        // Demonstrate we can expect a failure to throw an expected exception
        EXPECTED_FAILURE(assertException((void) 2, int, "no exception thrown"), "Validate exception not thrown fails");

        // Demonstrate we can expect a failure of an expected failure
        // Mind blowing, really... But, we have to test it....
        EXPECTED_FAILURE(EXPECTED_FAILURE(assert(true, "assert true to pass"), "Validate expected failure fails..."), "Validate expected failure");

        // Demonstrate we can expect a failure of an assert
        EXPECTED_FAILURE(assert(true, "assert true to pass"), "Validate expected failure fails...");
    }

    TEST_CASE(c)
    {
        assertFail("Intentional Failure");
    }
    
TEST_SUITE_END();