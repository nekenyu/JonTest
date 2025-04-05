#include "JonTest/TestSuite.h"
#include "JonTest/Assert.h"

/** Wrapper which INVERTS less than / greater than comparisons: a < b means Wrapper(a) > Wrapper(b).
 *
 * \note Equality and the equal portion of <= and >= is unaffected. 
 */
class InverseWrapper
{
public:
    typedef int Value;
    Value value;

    InverseWrapper(const Value& value)
    :value(value)
    {
        // Nothing to do
    }

    bool operator==(const InverseWrapper& right) const
    {
        // Unaffected by Inverse
        return value == right.value;
    }

    bool operator!=(const InverseWrapper& right) const
    {
        // Unaffected by Inverse
        return value != right.value;
    }

    bool operator <(const InverseWrapper& right) const
    {
        // Inverse negates
        return !(value < right.value);
    }

    bool operator >(const InverseWrapper& right) const
    {
        // Inverse negates
        return !(value > right.value);
    }

    bool operator <=(const InverseWrapper& right) const
    {
        // Inverse negates
        return (value == right.value) || ((*this) < right);
    }

    bool operator >=(const InverseWrapper& right) const
    {
        // Inverse negates
        return (value == right.value) || ((*this) > right);
    }
};

std::ostream& operator <<(std::ostream& out, const InverseWrapper& wrapper)
{
    out << "InverseWrapper(" << wrapper.value << ")";
    return out;
}

/** Given that lesser < greater, test assertLess() and assertGreater(), including failures.
 * 
 * \note This is a macro to enable stringification of the original arguments, instead of
 * 'lesser' and 'greater', and to enable test line numbers to work correctly.
 */
#define testLessGreater(lesser, greater) \
{ \
    assertLess(lesser, greater, "pass: lesser < greater"); \
    EXPECTED_FAILURE(assertLess(greater, lesser, "FAIL: greater < lesser"), "verify FAIL: greater < lesser"); \
    assertGreater(greater, lesser, "greater > lesser"); \
    EXPECTED_FAILURE(assertGreater(lesser, greater, "FAIL: lesser > greater"), "verify FAIL: FAIL: lesser > greater"); \
}

/** Given that lesser < greater, test assertLessEqual() and assertGreaterEqual(), including failures.
 * 
 * \note This is a macro to enable stringification of the original arguments, instead of
 * 'lesser' and 'greater', and to enable test line numbers to work correctly.
 */
#define testLessEqualGreaterEqual(lesser, greater) \
{ \
    assertLessEqual(lesser, lesser, "pass: lesser <= lesser"); \
    assertGreaterEqual(greater, lesser, "lesser >= lesser"); \
    \
    assertLessEqual(lesser, greater, "pass: lesser <= greater"); \
    EXPECTED_FAILURE(assertLessEqual(greater, lesser, "FAIL: greater <= lesser"), "verify FAIL: greater <= lesser"); \
    assertGreaterEqual(greater, lesser, "greater >= lesser"); \
    EXPECTED_FAILURE(assertGreaterEqual(lesser, greater, "FAIL: lesser >= greater"), "verify FAIL: FAIL: lesser >= greater"); \
}

TEST_SUITE(AssertComparison)

TEST_CASE(assertLessGreater_Numeric)
{
    testLessGreater(0, 1);
    testLessGreater('a', 'b');
    testLessGreater(0.0, 1.0);
}

TEST_CASE(assertLessGreater_Object)
{
    // NOTE: InverseWrapper negates the comparison tests
    testLessGreater(InverseWrapper(1), InverseWrapper(0));
    EXPECTED_FAILURE(testLessGreater(InverseWrapper(0), InverseWrapper(1)), "verify FAIL: inverse(0) vs. inverse(1)");
}

TEST_CASE(assertLessEqualGreaterEqual_Numeric)
{
    testLessEqualGreaterEqual(0, 1);
    testLessEqualGreaterEqual('a', 'b');
    testLessEqualGreaterEqual(0.0, 1.0);
}

TEST_CASE(assertLessEqualGreaterEqual_Object)
{
    // NOTE: InverseWrapper negates the comparison tests
    testLessEqualGreaterEqual(InverseWrapper(1), InverseWrapper(0));
}

TEST_CASE(assertEqual_Numeric)
{
    assertEqual(0, 0, "Same");
    EXPECTED_FAILURE(assertEqual(0, 1, "Not same"), "Verify FAIL: not same values");

    assertEqual('a', 'a', "Same");
    EXPECTED_FAILURE(assertEqual('a', 'b', "Not same"), "Verify FAIL: not same values");

    // Note: Of course, we do not test equality on floating point numbers...

    assertEqual(InverseWrapper(0), InverseWrapper(0), "Same .values");
    EXPECTED_FAILURE(assertEqual(InverseWrapper(0), InverseWrapper(1), "Not same"), "Verify FAIL: not same .values");
}

TEST_CASE(assertNotEqual_Numeric)
{
    assertNotEqual(0, 1, "Not same");
    EXPECTED_FAILURE(assertNotEqual(0, 0, "Same"), "Verify FAIL: same values");

    assertNotEqual('a', 'b', "Not same");
    EXPECTED_FAILURE(assertNotEqual('a', 'a', "Same"), "Verify FAIL: same values");

    // Note: Of course, we do not test inequality on floating point numbers...

    assertNotEqual(InverseWrapper(0), InverseWrapper(1), "Not not same .values");
    EXPECTED_FAILURE(assertNotEqual(InverseWrapper(0), InverseWrapper(0), "Same"), "Verify FAIL: same .values");
}

TEST_SUITE_END();