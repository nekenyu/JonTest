#include "JonTest/TestRunner.h"

#include "JonTest/Logger.h"
#include "JonTest/TestSuite.h"

#include <algorithm>
#include <map>
#include <utility>

namespace
{
    /** A parsed Test name as a Test Suite name (.first), and a Test
     * Case name (.second).
     * 
     * This refers to:
     * - An invalid TestName if both strings are empty strings.
     * - A Test Case if both strings are not empty.
     * - A Test Suite if the Test Suite name is not empty, but the
     *   Test Case name is empty.
     * \note This definition does not state with a Test Suite or Test
     * Case is in fact valid and defined; however, in context an
     * invalid TestName can mean invalid.
     */
    typedef std::pair<std::string, std::string> TestName;

    /** Parse test into a Test Suite Name and a Test Case name, which would be separated
     * by a ":".
     * 
     */ 
    TestName /// \returns parsed TestName, where invalid means not parseable
    parseTestName(
        const std::string& test ///< to parse
    )
    {
        const size_t separatorAt = test.find(":");
        if(std::string::npos == separatorAt)
        {
            return std::make_pair(test, std::string());
        }
        else if((0 == separatorAt) || (test.length() -1 == separatorAt))
        {
            return std::make_pair(std::string(), std::string());
        }
        else
        {
            return std::make_pair(test.substr(0, separatorAt), test.substr(separatorAt + 1));
        }
    }
}

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

bool TestRunner::isValid(
    const std::string& test
) const
{
    const TestName testName = parseTestName(test);

    if(testName.first.empty())
    {
        return false;
    }

    // Check Suite
    const auto suiteIter = suites.find(testName.first);
    if(suites.end() == suiteIter)
    {
        return false;
    }
    if(testName.second.empty())
    {
        return true;
    }

    // Check case
    return suiteIter->second->isValid(testName.second);
}

void TestRunner::listTestSuites(
    std::ostream& out
) const
{
    std::vector<std::string> names;
    for(const auto& nameSuite : suites)
    {
        names.push_back(nameSuite.first);
    }
    std::sort(names.begin(), names.end());

    out << "Available Test Suites:\n";
    for(const auto& name : names)
    {
        out << "\t" << name << "\n";
    }
    out << suites.size() << " Test Suites\n";
}

void TestRunner::listTestCases(
    std::ostream& out
) const
{
    std::vector<std::string> names;
    for(const auto& nameSuite : suites)
    {
        names.push_back(nameSuite.first);
    }
    std::sort(names.begin(), names.end());

    out << "Available Test Cases:\n";
    int count = 0;
    for(const auto& name : names)
    {
        const auto suite = suites.find(name);
        if(suites.end() == suite)
        {
            out << "INTERNAL ERROR: Failed to find Test Suite " << name << "\n";
        }
        else
        {
            count += suite->second->listTestCases(out);
        }
    }
    out << count << " Test Cases\n";
}

Count TestRunner::run(
    Logger& logger
) const
{
    logger.start();

    Count counts;
    for(const auto& nameSuite : suites)
    {
        counts += nameSuite.second->run(logger);
    }

    logger.end(counts);
    return counts;
}

Count TestRunner::run(
    Logger& logger,
    const TestNames& tests
) const
{
    if(tests.empty())
    {
        return run(logger);
    }

    logger.start();

    Count counts;
    for(const auto& test : tests)
    {
        // Convenience check the argument and get the iterator. Makes logic cleaner.
        const TestName testName = parseTestName(test);
        const auto& nameSuite = suites.find(testName.first);
        if(!isValid(test) || (suites.end() == nameSuite))
        {
            logger.errorCase(testName.first, testName.second, "not found", std::string("Test not found: \"") + test + "\"");
            logger.endCase(testName.first, "(suite)", false);
        }
        else if(testName.second.empty())
        {
            counts += nameSuite->second->run(logger);
        }
        else
        {
            counts += nameSuite->second->run(logger, testName.second);
        }
    }

    logger.end(counts);
    return counts;
}

}