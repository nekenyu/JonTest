#include "JonTest/TestSuite.h"
#include "JonTest/Assert.h"

#include <exception>
#include <iostream>
#include <string>

class MyTestException
: public std::exception
{
public:
    std::string info;

    inline virtual ~MyTestException()
    {
        // Nothing to do
    }

    inline explicit MyTestException(const char* info = "(MyTestException)") noexcept
    :info(info)
    {
        // Nothing to do
    }

    inline virtual const char* what() const noexcept
    {
        return info.c_str();
    }
};

void doNothing()
{
    // Nothing to do
}

TEST_SUITE(AssertException)

TEST_CASE(jontest_fail_exception)
{
    std::cout << "EXPECT: AssertException - jontest_fail_exception: case UNEXPECTED EXCEPTION: (MyTestException)" << std::endl;
    throw MyTestException();
}

TEST_CASE(expected_assertException)
{
    assertException(throw MyTestException(), MyTestException, "Failed to catch the exception!");
    assertException(throw MyTestException(), std::exception, "Failed to catch the exception!");
}

TEST_CASE(wrong_assertException)
{
    // TestCase::run() will always catch (...), so a wrong exception cannot be an "expectedFailure()"
    std::cout << "EXPECT: AssertException - wrong_assertException: case Internal Error: UNKNOWN EXCEPTION" << std::endl;
    assertException(throw int(5), MyTestException, "Failed to catch the int exception!")
}

TEST_CASE(did_not_assertException)
{
    expectedFailure(assertException(doNothing(), MyTestException, "Failed to throw an exception!"), "No exception thrown, so test failed");    
}

TEST_SUITE_END();