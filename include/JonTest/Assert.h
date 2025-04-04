#ifndef JON_TEST_ASSERT_H
#define JON_TEST_ASSERT_H

#include "JonTest/TestFailure.h"

/** Internal compiler function macro to support the assert* macros.
 * 
 * /warn Not for direct usage in testing.
 * 
 * Evaluates first and second once only. Compares precisely according to oper.
 * If the precise oper comparising fails, fails the current test, with the given
 * message as explanation.
 * 
 * Note: We cannot explicitly wrap binaryOperator in parenthesis for safety as it is an operator.
 */
#define jontest__assert2arg(first, second, message, binaryOperator) \
{ \
    const auto firstEval = (first); \
    const auto secondEval = (second); \
    if(!(firstEval binaryOperator secondEval)) \
    { \
        throw JonTest::TestFailure(__FILE__, __LINE__, (message), #first, firstEval, #second, secondEval, #binaryOperator); \
    } \
}

/// Explicitly fail the current test case with the given message as explanation.
#define assertFail(message) throw JonTest::TestFailure(__FILE__, __LINE__, (message), nullptr, nullptr, nullptr, nullptr, nullptr)

/// Fail this test if (first) is not true with the given message as explanation.
#define assert(first, message)         jontest__assert2arg(first, true, message, ==)

/// Fail this test if (first) is not true with the given message as explanation.
#define assertTrue(first, message)     jontest__assert2arg(first, true, message, ==)

/// Fail this test if (first) is not false with the given message as explanation.
#define assertFalse(first, message)    jontest__assert2arg(first, false, message, ==)

/// Fail this test if (first) is not a nullptr with the given message as explanation.
#define assertNullPtr(first, message)  jontest__assert2arg(first, nullptr, message, ==)

/// Fail this test if (first) is nullptr with the given message as explanation.
#define assertValidPtr(first, message) jontest__assert2arg(first, nullptr, message, !=)

/// Fail this test if (first) is not equal to (second) with the given message as explanation.
#define assertEqual(first, second, message)        jontest__assert2arg(first, second, message, ==)

/// Fail this test if (first) is equal to (second) with the given message as explanation.
#define assertNotEqual(first, second, message)     jontest__assert2arg(first, second, message, !=)

/// Fail this test if (first) is not less than (second) with the given message as explanation.
#define assertLess(first, second, message)         jontest__assert2arg(first, second, message, <)

/// Fail this test if (first) is not less than or equal to (second) with the given message as explanation.
#define assertLessEqual(first, second, message)    jontest__assert2arg(first, second, message, <=)

/// Fail this test if (first) is not greater than (second) with the given message as explanation.
#define assertGreater(first, second, message)      jontest__assert2arg(first, second, message, >)

/// Fail this test if (first) is not greater than or equal to (second) with the given message as explanation.
#define assertGreaterEqual(first, second, message) jontest__assert2arg(first, second, message, >=)

/** Fail this test if (expression) does not throw the expected exception or a derived class exception with the given message as explanation.
* Note: We cannot explicitly wrap expected in parenthesis for safety as it is an operator.
*/
#define assertException(expression, expected, message) { \
    bool passed = false;\
    try { (expression); passed = true; } \
    catch (expected& object) { } \
    if(passed) \
    { \
        throw JonTest::TestFailure(__FILE__, __LINE__, (message), nullptr, nullptr, nullptr, nullptr, nullptr); \
    } \
}

/** Fail this test if evaluating (expression) does not result itself in a failed test.
 * 
 * If evaluating (expression) does result in a failed test, this test will pass.
 */
#define expectedFailure(expression, message) assertException(expression, JonTest::TestFailure, message)

#endif