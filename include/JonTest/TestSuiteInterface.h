#ifndef JON_TEST_TEST_SUITE_INTERFACE_H
#define JON_TEST_TEST_SUITE_INTERFACE_H

#include "JonTest/Logger.h"

namespace JonTest
{

class Logger;

/** Interface for Test Suites.
 * 
 * All Test Suites call setup() before and teardown() after each test case. Since not all Test Suitess
 * need this behavior, a default do-nothing implementation is provided for each.
 * 
 * All Test Suites can be run() by the TestRunner -- as determined by their implementation.
 */
class TestSuiteInterface
{
public:
    /// Destructor -- does nothing
    virtual ~TestSuiteInterface();

    /** The Test Suite runsthis prior to each test case. A default do-nothing implementation is provided.
     */
    virtual void setup();

    /** The Test Suite runs this after to each test case. A default do-nothing implementation is provided.
     */
    virtual void teardown();

    /** Determine if caseName can be run in this Test Suite,
     */
    virtual bool /// \returns true if caseName can be run, otherwise false
    isValid(
        const std::string& caseName
    ) const = 0;

    /** List available Test Cases to out.
     */
    virtual int ///< \returns the number of test cases
    listTestCases(
        std::ostream& out
    ) const = 0;

    /** Runs all Test Cases in this Test Suite.
     */
    virtual Count /// \returns the Count of tests run and tests failed in this Test Suite.
    run(
        Logger& logger ///< to log events of running the test suite and cases
    ) = 0;

    /** Runs the given testCase in this Test Suite.
     * 
     * \note If testCase is not valid, it will result in an error, and the
     * returned count of running 1 test, and failing 1 test.
     */
    virtual Count /// \returns the Count of tests run and tests failed in this Test Suite.
    run(
        Logger& logger, ///< to log events of running the test suite and cases
        const std::string& testCase ///< to run
    ) = 0;
};

}

#endif