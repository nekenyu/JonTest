#ifndef JON_TEST_TEST_CASE_H
#define JON_TEST_TEST_CASE_H

#include "JonTest/Logger.h"
#include "JonTest/TestFailure.h"

#include <string>

namespace JonTest
{

/** Defines and runs a single Test Case within a Test Suite.
 * 
 * \tparam TestSuiteDerived The actual Test Suite class, required for pointer to member.
 */
template <typename TestSuiteDerived>
class TestCase
{
public:
    /// The actual Test Suite class
    typedef TestSuiteDerived TestSuite;

    /// The actual Test Suite Method type for test cases
    typedef void (TestSuite::*TestCaseMethod)();

    /// Name of the Test Case
    std::string name;

    /// TestSuite method of the Test Case
    TestCaseMethod testCaseMethod;

    /** Creates TestCase and adds the Test Case to the suite.
     */
    static TestCase createAndAdd(
        TestSuite& suite, ///< Test Suite to add this to
        const char* const testCaseName, ///< Name of the Test Case
        TestCaseMethod const testCaseMethod ///< TestSuite method of the Test Case
    )
    {
        suite.add(testCaseName, testCaseMethod);
        return TestCase(testCaseName, testCaseMethod);
    }

    /** Default initializer for use in STL containers.
    */
    TestCase() = default;

    /** Default copy constructor for use in STL containers.
    */
   TestCase(const TestCase& right) = default;

    /** Create Test Case by name for given testCaseMethod in TestSuite.
    */
    TestCase(
        const char* const testCaseName, ///< Name of the Test Case
        TestCaseMethod const testCaseMethod ///< TestSuite method of the Test Case
    )
    : name(testCaseName),
    testCaseMethod(testCaseMethod)
    {
        // Nothing to do
    }

    /** Do nothing destructor.
     */
    ~TestCase()
    {
        // Nothing to do. DO NOT DELETE pointer-to-member testCaseMethod.
    }

    /** Run this Test Case as part of suite, logging events to logger.
     */
    bool /// \returns true for pass, false for fail or error
    run(
        TestSuite& suite, ///< Test Suite this Test Case belongs to
        Logger& logger ///< Receiver of events from the execution of this Test Case
    ) const
    {
        logger.startCase(suite.getName(), name);

        if(nullptr == testCaseMethod)
        {
            logger.errorCase(suite.getName(), name, "(internal)", "Internal Error: MISSING test case method");
            return false;
        }
    
        // Note: We use compressed/multiple-statements-per-line for clarity here
        bool setupPassed = false;
        try { suite.setup(); setupPassed = true; }
        catch(TestFailure& failure)       { logger.failCase(suite.getName(), name, "setup", failure); }
        catch(std::exception& unexpected) { logger.exceptionCase(suite.getName(), name, "setup", unexpected); }
        catch(...)                        { logger.errorCase(suite.getName(), name, "setup", "UNKNOWN EXCEPTION"); }

        bool casePassed = false;
        if(setupPassed) {
            try { (suite.* testCaseMethod)(); casePassed = true; }
            catch(TestFailure& failure)       { logger.failCase(suite.getName(), name, "case", failure); }
            catch(std::exception& unexpected) { logger.exceptionCase(suite.getName(), name, "case", unexpected); }
            catch(...)                        { logger.errorCase(suite.getName(), name, "case", "UNKNOWN EXCEPTION"); }
        }
        
        bool teardownPassed = false;
        try { suite.teardown(); teardownPassed = true; }
        catch(TestFailure& failure)       { logger.failCase(suite.getName(), name, "teardown", failure); }
        catch(std::exception& unexpected) { logger.exceptionCase(suite.getName(), name, "teardown", unexpected); }
        catch(...)                        { logger.errorCase(suite.getName(), name, "teardown", "UNKNOWN EXCEPTION"); }

        const bool passed = setupPassed && casePassed && teardownPassed;            
        logger.endCase(suite.getName(), name, passed);
        return passed;
    }
};

}

#endif
