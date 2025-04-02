#include "JonTest/TestSuite.h"

#include "JonTest/Count.h"

#include <iostream>

TEST_SUITE(SimpleTest2)

    void setup()
    {
        std::cout << "\t\t\tSimpleTest2: setup()";
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
        throw JonTest::TestFailure();
    }
    
TEST_SUITE_END();