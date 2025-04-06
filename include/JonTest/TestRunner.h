#ifndef JON_TEST_TEST_RUNNER_H
#define JON_TEST_TEST_RUNNER_H

#include "JonTest/Count.h"

#include <map>
#include <ostream>
#include <string>
#include <vector>

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
    /// List of Test Names as: "<suite>" or "<suite>:<case>"
    typedef std::vector<std::string> TestNames;

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

    /** Determine if test can be run as one of: a valid Test Suite,
     * or Test Suite:Test Case.
     */
    bool /// \returns true if test can be run, otherwise false
    isValid(
        const std::string& test
    ) const;

    /** List available Test Suites to out.
     */
    void listTestSuites(
        std::ostream& out
    ) const;

    /** List available Test Cases to out.
     */
    void listTestCases(
        std::ostream& out
    ) const;

    /** Run all tests that have been add()ed.
     */
    Count ///< \return Count of tests run and tests failed fails.
    run(
        Logger& logger ///< To report status to
    ) const;

    /** Run the specified tests.
     * 
     * Any element of tests that fails isValid(test) will be reported
     * as an error and test failure.
     * 
     * \return Count of tests run and tests failed fails.
     */
    Count ///< \return Count of tests run and tests failed fails.
    run(
        Logger& logger, ///< To report status to
        const TestNames& tests ///< To run
    ) const;
};

}

#endif