#ifndef JON_TEST_ASSERT_H
#define JON_TEST_ASSERT_H

#include "JonTest/TestFailure.h"

#define assertFail(msg) throw JonTest::TestFailure(__FILE__, __LINE__, (msg), nullptr, nullptr, nullptr, nullptr, nullptr);

// TODO: Log assert, #first, firstEval, #second, secondEval
#define assert__2(first, second, msg, oper) { \
    const auto firstEval = (first); const auto secondEval = (second); \
    if(!(firstEval oper secondEval)) { throw JonTest::TestFailure(__FILE__, __LINE__, (msg), #first, firstEval, #second, secondEval, #oper); } \
}

#define assertEqual(first, second, msg)        assert__2(first, second, msg, ==);
#define assertNotEqual(first, second, msg)     assert__2(first, second, msg, !=);
#define assertLess(first, second, msg)         assert__2(first, second, msg, <);
#define assertLessEqual(first, second, msg)    assert__2(first, second, msg, <=);
#define assertGreater(first, second, msg)      assert__2(first, second, msg, >);
#define assertGreaterEqual(first, second, msg) assert__2(first, second, msg, >=);

// TODO: Log assert, #first, firstEval
#define assert(first, msg)         assert__2(first, true, msg, ==);
#define assertTrue(first, msg)     assert__2(first, true, msg, ==);
#define assertFalse(first, msg)    assert__2(first, false, msg, ==);
#define assertNullPtr(first, msg)  assert__2(first, nullptr, msg, ==);
#define assertValidPtr(first, msg) assert__2(first, nullptr, msg, !=);


#endif