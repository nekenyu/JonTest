#include "JonTest/TestSuite.h"

#include <iostream>

/** Example execution of JonTest showing via std::cout the execution of test cases 
 *  with setup and teardown methods.
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
        std::cout << "\t\t\tSimpleTest: setup()";
    }

    void teardown()
    {
        std::cout << " teardown()" << std::endl;
    }

    TEST_CASE(a)
    {
        std::cout << " a()";
    }

    TEST_CASE(b)
    {
        std::cout << " b()";
    }
 
    TEST_CASE(c)
    {
        std::cout << " c()";
    }

TEST_SUITE_END()