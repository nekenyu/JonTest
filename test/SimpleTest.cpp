#include "JonTest/TestSuite.h"

#include <iostream>

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