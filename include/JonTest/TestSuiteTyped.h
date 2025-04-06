#ifndef JON_TEST_TEST_SUITE_TYPED_H
#define JON_TEST_TEST_SUITE_TYPED_H

#include "JonTest/Count.h"
#include "JonTest/Logger.h"
#include "JonTest/TestCase.h"
#include "JonTest/TestRunner.h"
#include "JonTest/TestSuiteInterface.h"

#include <algorithm>
#include <map>
#include <string>
#include <vector>

namespace JonTest
{

/** Holds and runs Test Cases as a single Test Suite.
 * 
 * Main automatic Test Suite implementation with TestSuite naming the derived class
 * for pointer-to-member.
 * 
 * Provides the map of Test Case name to 
 * 
 * \tparam TestSuiteDerived The actual Test Suite class, required for TestCase<>.
 */
template <typename TestSuiteDerived>
class TestSuiteTyped : public TestSuiteInterface
{
public:
    /// The actual Test Suite class
    typedef TestSuiteDerived TestSuite;

    /// The actual Test Suite Method type for test cases
    typedef void (TestSuite::*TestCaseMethod)();

private:
    /// Name of this Test Suite
    const std::string suiteName;

    /// Map of Test Case name to TestCase<TestSuite> cases
    std::map<std::string, TestCase<TestSuite>> cases;

protected:
    /** Create the Test Suite by name and add it to the TestRunner singleton.
     * 
     * Restricted to derived classes.
     */
    TestSuiteTyped(
        const char * const suiteName ///< Name of this test suite
    )
    : suiteName(suiteName)
    {
        TestRunner::get().add(suiteName, this);
    }

    virtual ~TestSuiteTyped() { }

public:
    /** Returns the name of this Test Suit.
    */
    const std::string& ///< \returns the name of this Test Suite.
    getName() const {
        return suiteName;
    }

    virtual bool /// \returns true if caseName can be run, otherwise false
    isValid(
        const std::string& caseName
    ) const
    {
        return cases.end() != cases.find(caseName);
    }

    /** Add TestCaseMethod by name to this Test Suite.
     */
    void add(
        const char* const testCaseName, ///< Name of the Test Case
        TestCaseMethod const testCaseMethod ///< TestSuite method of the Test Case
    )
    {
        // \todo Error check for overwrite
        cases[testCaseName] = TestCase<TestSuite>(testCaseName, testCaseMethod);
    }

    /** List available Test Cases to out.
     */
    virtual int ///< \returns the number of test cases
    listTestCases(
        std::ostream& out
    ) const
    {
        std::vector<std::string> names;
        for(const auto& testCase : cases)
        {
            names.push_back(testCase.first);
        }
        std::sort(names.begin(), names.end());
    
        for(const auto& name : names)
        {
            out << "\t" << suiteName << ":" << name << "\n";
        }
    
        return cases.size();
    }

    /** Run all Test Cases in the Test Suite giving events to logger.
     */
    virtual Count ///< \returns Count of tests run and failed in this Test Suite.
    run(
        Logger& logger ///< The logger for events issued while running this test
    )
    {
        logger.startSuite(suiteName);

        Count count;
        for(auto& nameCase : cases)
        {
            ++count.count;
            const bool passed = nameCase.second.run(static_cast<TestSuite&>(*this), logger);
            if(! passed)
            {
                ++count.fails;
            }
        }
    
        logger.endSuite(suiteName, count);
        return count;
    }

    /** Runs the given testCase in this Test Suite.
     * 
     * \note If testCase is not valid, it will result in an error, and the
     * returned count of running 1 test, and failing 1 test.
     */
    virtual Count /// \returns the Count of tests run and tests failed in this Test Suite.
    run(
        Logger& logger, ///< to log events of running the test suite and cases
        const std::string& testCase ///< to run
    )
    {
        // Skip reporting the suite on individual tests
        Count count;
        ++count.count;

        const auto nameCase = cases.find(testCase);
        if(cases.end() == nameCase)
        {
            ++count.fails;
            return count;
        }

        const bool passed = nameCase->second.run(static_cast<TestSuite&>(*this), logger);
        if(! passed)
        {
            ++count.fails;
        }

        return count;
    }

};

}

#endif
