#ifndef JON_TEST_TEST_SUITE_H
#define JON_TEST_TEST_SUITE_H

#include "JonTest/TestCase.h"
#include "JonTest/TestSuiteTyped.h"

/** Defines a Test Suite named testSuiteName.
 * 
 * \param testSuiteName Name of Test Suite suitable for a class name.
 * 
 * This creates a class named testSuiteName obeying the TestSuiteInterface,
 * and a single unique instance of the class which is automatically registered
 * with TestRunner.
 * 
 * When running this Test Suite, each Test Case defined by TEST_CASE() will be
 * called as:
 * - `testSuiteName::setup()`
 * - `testSuiteName::testCaseName()`
 * - `testSuiteName::teardown()`
 * 
 * The user is free to add data members and member functions to support testing
 * provided:
 * - They do not have conflicting names with TestSuiteTyped<>
 * - They do not require memberwise initialization within testSuiteName's constructor(s)
 * 
 * Typical usage:
 * \code{.cpp}
 * TEST_SUITE(MyTestSuite)
 * 
 * std::string value1;
 * std::string value2;
 * 
 * void setup()
 * {
 *     value1 = "some string value";
 *     value2 = "another";
 * }
 * 
 * void teardown()
 * {
 *     value1.clear()
 *     value2.clear*()
 * }
 * 
 * TEST_CASE(testFeatureA)
 * {
 *     ....
 * }
 * 
 * TEST_CASE(testFeatureB)
 * {
 *     ....
 * }
 * 
 * ...
 * 
 * END_TEST_SUITE()
 * \endcode
 * 
 * \see TEST_CASE()
 * \see TEST_SUITE_END()
 */
#define TEST_SUITE(testSuiteName) \
namespace { \
class testSuiteName \
: public JonTest::TestSuiteTyped<testSuiteName> \
{ \
private: \
    typedef testSuiteName SuiteName; \
public: \
    testSuiteName() : TestSuiteTyped(#testSuiteName) {}

/** Finish definition of a Test Suite started with TEST_SUITE().
 * 
 * \see TEST_SUITE()
 */
#define TEST_SUITE_END() \
} test; \
}

/** Defines a Test Case method named testCaseName within a Test Suite
 * defined by TEST_SUITE().
 * 
 * \param testCaseName Name of Test Suite suitable for a class name.
 * 
 * This creates a function named testCaseName and a helper named testCaseName
 * with "_holder" appended to automatically register the Test Case.
 * 
 * \see TEST_SUITE()
*/
#define TEST_CASE(testCaseName) \
JonTest::TestCase<SuiteName> testCaseName ##_holder = JonTest::TestCase<SuiteName>::createAndAdd(*this, #testCaseName, &SuiteName::testCaseName); \
void testCaseName()

#endif