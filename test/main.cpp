#include "JonTest/TestRunner.h"

#include <iostream>

int main(int argc, char**argv)
{
    JonTest::TestRunner::get().run(std::cout, true);
}