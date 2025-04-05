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

    /** Runs all Test Cases in this Test Suite.
     * 
     * \returns the Count of tests run and tests failed in this Test Suite.
     */
    virtual Count run(
        Logger& logger ///< to log events of running the test suite and cases
    ) = 0;
};

}

#endif