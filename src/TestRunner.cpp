#include "JonTest/TestRunner.h"

#include "JonTest/TestSuite.h"

#include <iostream>
#include <map>
#include <string>

namespace JonTest
{
TestRunner& TestRunner::get()
{
    static TestRunner instance;
    return instance;
}

void TestRunner::add(const char* const name, TestSuiteBase* const suite)
{
    // TODO: Error check this isn't overriding an existing test
    suites[name] = suite;
}

bool TestRunner::run(std::ostream& out, bool verbose)
{
    if(verbose)
    {
        out << "Beginning All Test Suites" << std::endl;
    }

    Count counts;
    for(const auto& nameSuite : suites)
    {
        counts += nameSuite.second->run(out, verbose);
    }

    out << "Tests Complete:\n" 
        << "\tRun: " << counts.count << "\t Fails: " << counts.fails << std::endl;

    return 0 != counts.fails;
}

}