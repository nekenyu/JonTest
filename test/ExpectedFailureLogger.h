#ifndef TEST_EXPECTED_FAILURE_LOGGER_H
#define TEST_EXPECTED_FAILURE_LOGGER_H

#include "JonTest/Logger.h"

#include <map>
#include <ostream>

/** UNIQUE TO TESTING JonTest: A Logger that verifies Test Cases that can only be
 * verified by failing tests.
 * 
 * All test case names beginning with expectedFailCasePrefix are expected to fail
 * in some fashion. All such tests will be captured at runtime, its events prefixed
 * "EXPECT:", and counted when failed as expected. At the end of testing, a report
 * is issued (based on verbose), and expected fails removed from fail count and
 * program return code.
 * 
 * Uses the standard StreamLogger for normal output, except when suppressed for
 * expected failures that fail when verbpse.
 */
class ExpectedFailureLogger
: public JonTest::StreamLogger
{
public:
    /// Prefix of all test case names that are expected to fail.
    const std::string expectedFailCasePrefix = "jontest_fail_";

private:
    /** Map within each Test Suite of expected failure Test Case to result.
     * 
     * Result:
     * - true: test passed, in error since these are only expected failures
     * - false: test failed, as expected
     */
    typedef std::map<std::string, bool> CaseResults; 

    /** Map of Test Suite to CaseResults of expected failures.
     */
    typedef std::map<std::string, CaseResults> SuiteResults;

    /** Map of Test Suite to Test Case to result of expected failure test.
     * 
     * Result:
     * - true: test passed, in error since these are only expected failures
     * - false: test failed, as expected
     */
    SuiteResults results;

    /// Number of expectedFailCasePrefix Test Cases found
    int expected = 0;

    /// Number of expectedFailCasePrefix Test Cases that failed, as expected
    int expectedFails = 0;

public:
    /// Destructor, does nothing.
    virtual ~ExpectedFailureLogger();

    /** Construct a Stream Logger handling expected failure test cases
     */
    ExpectedFailureLogger(
        std::ostream& out,  ///< Stream to write to
        bool verbose ///< Simple level of verbosity: true for all events, false for critical
    );

    /** Get the number of exptected test failures that failed.
     */
    int /// \returns The number of expected test failures that failed.
    getExpectedFailuresFailed() const;

private:
    /** Determine if this Test Case is expected to fail.
     */
    bool /// \returns true if this test case is expected to faile, otherwise false
    isExpectedToFail(
        const std::string&, ///< Test Suite name to consider
        const std::string& caseName ///< Test Case name to consider
    ) const;

    /** Determine it this case should be logged.
     * 
     * Additionally, records all Test Cases that are expected to fail,
     * and prefixes expected failure logging with "EXPECT:".
     */
    bool // true if the test was not expected to fail, or if it is verbose, otherwise false
    shouldLog(
        const std::string& suiteName, ///< Test Suite Name to consider
        const std::string& caseNamee ///< Test Case name to consider
    );

public:
    virtual void errorCase(
        const std::string& suiteName,
        const std::string& caseName,
        const std::string& casePart,
        const std::string& message
    );

    virtual void failCase(
        const std::string& suiteName,
        const std::string& caseName,
        const std::string& casePart,
        const JonTest::TestFailure& failure
    );

    virtual void exceptionCase(
        const std::string& suiteName,
        const std::string& caseName,
        const std::string& casePart,
        const std::exception& unexpected
    );

    virtual void endCase(
        const std::string& suiteName,
        const std::string& caseName,
        const bool pass
    );

    virtual void end();
};

#endif