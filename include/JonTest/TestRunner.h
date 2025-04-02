#ifndef JON_TEST_TEST_RUNNER_H
#define JON_TEST_TEST_RUNNER_H

#include "JonTest/Count.h"

#include <map>
#include <string>
#include <ostream>

namespace JonTest
{

class TestSuiteBase;

class TestRunner
{
private:
    std::map<std::string, JonTest::TestSuiteBase*> suites;
    inline TestRunner() {}

public:
    static TestRunner& get();

    void add(const char* const name, TestSuiteBase* const suite);

    bool run(std::ostream& out, bool verbose = false);
};

}

#endif