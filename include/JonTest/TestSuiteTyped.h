#ifndef JON_TEST_TEST_SUITE_TYPED_H
#define JON_TEST_TEST_SUITE_TYPED_H

#include "JonTest/Count.h"
#include "JonTest/Logger.h"
#include "JonTest/TestCase.h"
#include "JonTest/TestRunner.h"
#include "JonTest/TestSuiteInterface.h"

#include <map>
#include <string>

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
    const std::string name;

    /// Map of Test Case name to TestCase<TestSuite> cases
    std::map<std::string, TestCase<TestSuite>> cases;

protected:
    /** Create the Test Suite by name and add it to the TestRunner singleton.
     * 
     * Restricted to derived classes.
     */
    TestSuiteTyped(
        const char * const name ///< Name of this test suite
    )
    : name(name)
    {
        TestRunner::get().add(name, this);
    }

    virtual ~TestSuiteTyped() { }

public:
    /** Returns the name of this Test Suit.
    */
    const std::string& ///< \returns the name of this Test Suite.
    getName() const {
        return name;
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

    /** Run all Test Cases in the Test Suite giving events to logger.
     */
    virtual Count ///< \returns Count of tests run and failed in this Test Suite.
    run(
        Logger& logger ///< The logger for events issued while running this test
    )
    {
        logger.startSuite(name);

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
    
        logger.endSuite(name, count);
        return count;
    }
};

}

#endif