#ifndef JON_TEST_ASSERT_H
#define JON_TEST_ASSERT_H

#include "JonTest/TestFailure.h"

#define assert__2(first, second, msg, oper) { \
    const auto firstEval = (first); const auto secondEval = (second); \
    if(!(firstEval oper secondEval)) { throw JonTest::TestFailure(__FILE__, __LINE__, (msg), #first, firstEval, #second, secondEval, #oper); } \
}

#define assertFail(msg) throw JonTest::TestFailure(__FILE__, __LINE__, (msg), nullptr, nullptr, nullptr, nullptr, nullptr)

#define assert(first, msg)         assert__2(first, true, msg, ==)
#define assertTrue(first, msg)     assert__2(first, true, msg, ==)
#define assertFalse(first, msg)    assert__2(first, false, msg, ==)
#define assertNullPtr(first, msg)  assert__2(first, nullptr, msg, ==)
#define assertValidPtr(first, msg) assert__2(first, nullptr, msg, !=)

#define assertEqual(first, second, msg)        assert__2(first, second, msg, ==)
#define assertNotEqual(first, second, msg)     assert__2(first, second, msg, !=)
#define assertLess(first, second, msg)         assert__2(first, second, msg, <)
#define assertLessEqual(first, second, msg)    assert__2(first, second, msg, <=)
#define assertGreater(first, second, msg)      assert__2(first, second, msg, >)
#define assertGreaterEqual(first, second, msg) assert__2(first, second, msg, >=)

#define assertException(expr, expect, msg) { \
    bool passed = false;\
    try { (expr); passed = true; } \
    catch( expect& object ) { } \
    if(passed) { throw JonTest::TestFailure(__FILE__, __LINE__, (msg), nullptr, nullptr, nullptr, nullptr, nullptr); } \
}

#define expectedFailure(expr, msg) { \
    bool passed = false;\
    try { (expr); passed = true; } \
    catch (JonTest::TestFailure& failure) { }  \
    if(passed) { throw JonTest::TestFailure(__FILE__, __LINE__, (msg), nullptr, nullptr, nullptr, nullptr, nullptr); } \
}

#endif