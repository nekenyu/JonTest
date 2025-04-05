#ifndef JON_TEST_TEST_RUNNER_H
#define JON_TEST_TEST_RUNNER_H

#include "JonTest/Count.h"

#include <map>
#include <string>

namespace JonTest
{

class Logger;
class TestSuiteInterface;

/** Singleton that collects all TEST_SUITE()s, to run on demand.
 */
class TestRunner
{
private:
    /// Mapping of test suite name to test suite.
    std::map<std::string, TestSuiteInterface*> suites;

    // Private default constructor for singleton
    TestRunner() = default;

public:
    /** Get the singleton.
    *
    * \returns the singleton.
    */
    static TestRunner& get();

    /** Add the suite by name.
     */
    void add(
        const char* const name, ///< Name of suite
        TestSuiteInterface* const suite ///< Test Suite
    );

    /** Run all tests that have been add()ed.
     * 
     * \return Count of tests run and tests failed fails.
     */
    Count run(
        Logger& logger ///< To report status to
    );
};

}

#endif