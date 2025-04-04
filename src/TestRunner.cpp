#include "JonTest/TestRunner.h"

#include "JonTest/Logger.h"
#include "JonTest/TestSuite.h"

#include <map>

namespace JonTest
{
TestRunner& TestRunner::get()
{
    static TestRunner instance;
    return instance;
}

void TestRunner::add(
    const char* const name,
    TestSuiteInterface* const suite
)
{
    // TODO: Error check this isn't overriding an existing test
    suites[name] = suite;
}

Count TestRunner::run(
    Logger& logger
)
{
    logger.start();

    Count counts;
    for(const auto& nameSuite : suites)
    {
        counts += nameSuite.second->run(logger);
    }

    logger.end();
    return counts;
}

}