#include "ExpectedFailureLogger.h"

#include "JonTest/Count.h"

#include <iostream>
#include <string>

ExpectedFailureLogger::~ExpectedFailureLogger()
{
    // Nothing to do
}

ExpectedFailureLogger::ExpectedFailureLogger(
    std::ostream& out,
    bool verbose
)
: StreamLogger(out, verbose)
{
    out << "NOTICE: expected failure Test Cases are prefixed with: jontest_fail_" << std::endl;
}

int ExpectedFailureLogger::getExpectedFailuresFailed() const
{
    return expectedFails;
}

bool ExpectedFailureLogger::isExpectedToFail(
    const std::string&,
    const std::string& caseName
) const
{
    return 0 == caseName.find(expectedFailCasePrefix);
}

bool ExpectedFailureLogger::shouldLog(
    const std::string& suiteName,
    const std::string& caseName
)
{
    // Log the unexpected, but do nothing else
    if(!isExpectedToFail(suiteName, caseName))
    {
        return true;
    }
    
    // Record this was found, as if it passed in error
    results[suiteName][caseName] = true;

    // Log this expected if we are verbose
    if(verbose)
    {
        out << "EXPECT:";
        return true;
    }

    // Expecteds are not logged when not verbose
    return false;
}

void ExpectedFailureLogger::errorCase(
    const std::string& suiteName,
    const std::string& caseName,
    const std::string& casePart,
    const std::string& message
)
{
    if(shouldLog(suiteName, caseName))
    {
        StreamLogger::errorCase(suiteName, caseName, casePart, message);
    }
}

void ExpectedFailureLogger::failCase(
    const std::string& suiteName,
    const std::string& caseName,
    const std::string& casePart,
    const JonTest::TestFailure& failure
)
{
    if(shouldLog(suiteName, caseName))
    {
        StreamLogger::failCase(suiteName, caseName, casePart, failure);
    }
}

void ExpectedFailureLogger::exceptionCase(
    const std::string& suiteName, ///< Name of test suite
    const std::string& caseName, ///< Name of test case
    const std::string& casePart, ///< Part of the test case: setup, case, or teardown
    const std::exception& unexpected ///< Unexpected exception
)
{
    if(shouldLog(suiteName, caseName))
    {
        StreamLogger::exceptionCase(suiteName, caseName, casePart, unexpected);
    }
}

void ExpectedFailureLogger::endCase(
    const std::string& suiteName,
    const std::string& caseName,
    const bool pass
)
{
    if(shouldLog(suiteName, caseName))
    {
        StreamLogger::endCase(suiteName, caseName, pass);
    }

    // Update expected metrics and results
    if(isExpectedToFail(suiteName, caseName))
    {
        // Record this was failed as expected (true) or passed unexpectedly (false)
        results[suiteName][caseName] = pass;

        // Count metrics
        ++expected;
        if(!pass)
        {
            ++expectedFails;
        }
    }    
}

void ExpectedFailureLogger::end()
{
    out << "Expected Failures: Properly failed " << expectedFails << " of " << expected << ", and removed from failure count and exit code\n";

    // Skip details when all found and not verbose
    if((expectedFails == expected) && !verbose)
    {
        return;
    }
    
    out << "Status\t\tTest Suite - Test Case\n";
    for(const auto& suiteResult : results)
    {
        const std::string& suiteName = suiteResult.first;
        for(const auto& caseResult : suiteResult.second)
        {
            const std::string& caseName = caseResult.first;
            const bool passedInError = caseResult.second;
            if(verbose || passedInError)
            {
                const std::string result = passedInError ? "ERROR   " : "EXPECTED";
                out << result << "\t" << suiteName << " - " << caseName << "\n";
            }
            }
    }
}