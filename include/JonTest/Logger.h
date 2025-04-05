#ifndef JON_TEST_LOGGER_H
#define JON_TEST_LOGGER_H

#include "JonTest/Count.h"

#include <exception>
#include <ostream>
#include <string>

namespace JonTest
{

class TestFailure;

/** Interface for logging events while running tests.
 */
class Logger
{
public:
    /// Destructor -- does nothing
    virtual ~Logger();

    /// Start of all testing
    virtual void start() = 0;

    /// Start of test suite
    virtual void startSuite(
        const std::string& suiteName ///< Name of test suite
    ) = 0;

    /// Start of test case
    virtual void startCase(
        const std::string& suiteName, ///< Name of test suite
        const std::string& caseName ///< Name of test case
    ) = 0;

    /// Unexpected error occurred during a part of the test case
    virtual void errorCase(
        const std::string& suiteName, ///< Name of test suite
        const std::string& caseName, ///< Name of test case
        const std::string& casePart, ///< Part of the test case: setup, case, or teardown
        const std::string& message ///< Error message
    ) = 0;

    /// Test failure occurred during a part of the case
    virtual void failCase(
        const std::string& suiteName, ///< Name of test suite
        const std::string& caseName, ///< Name of test case
        const std::string& casePart, ///< Part of the test case: setup, case, or teardown
        const TestFailure& failure ///< TestFailure as recorded
    ) = 0;

    /// Unexpected exception occurred during a part of the case
    virtual void exceptionCase(
        const std::string& suiteName, ///< Name of test suite
        const std::string& caseName, ///< Name of test case
        const std::string& casePart, ///< Part of the test case: setup, case, or teardown
        const std::exception& unexpected ///< Unexpected exception
    ) = 0;

    /// End of test case, with record pass or fail 
    virtual void endCase(
        const std::string& suiteName, ///< Name of test suite
        const std::string& caseName, ///< Name of test case
        const bool pass ///< true if passed, false if failed
    ) = 0;

    /// End of test suite, with count of tests run and failed for that suite alone
    virtual void endSuite(
        const std::string& suiteName, ///< Name of test suite
        const Count& count ///< Count of tests run and failed in this suite
    ) = 0;

    /// End of all testing, suitable to output
    virtual void end(
        const Count& count ///< Count of Test Cases run, and Test Cases failed
    ) = 0;
};

/** Stream-based Logger for events while running tests.
 * 
 * Test cases are counted as:
 * - count: Number of test cases that have finished
 * - fails: Number of test cases that have failed
 * \note These are defined by calls to endCase(), not by potententially multiple calls between
 * setup(), the test case, and teardown().
 */
class StreamLogger : public Logger
{
protected:
    /// Stream to write to
    std::ostream& out;

    /// Simple level of verbosity: true for all events, false for critical
    const bool verbose;

public:
    /** Construct the Stream Logger to write to out with the given verbosity.
     */
    StreamLogger(
        std::ostream& out,  ///< Stream to write to
        bool verbose ///< Simple level of verbosity: true for all events, false for critical
    );

    /// Destructor -- does nothing
    virtual ~StreamLogger();

    virtual void start();
    
    virtual void startSuite(
        const std::string& suiteName
    );

    virtual void startCase(
        const std::string& suiteName,
        const std::string& caseName
    );

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
        const TestFailure& failure
    );

    /// Unexpected exception occurred during a part of the case
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

    virtual void endSuite(
        const std::string& suiteName,
        const Count& count
    );

    virtual void end(
        const Count& count
    );
};

}

#endif
