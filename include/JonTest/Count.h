#ifndef JON_TEST_COUNT_H
#define JON_TEST_COUNT_H

namespace JonTest
{

/** Count of tests run, and fails.
 */
class Count
{
public:
    /** Number of tests that have been run.
     */
    int count = 0;

    /** Number of tests that have failed.
    */
    int fails = 0;

    /** Add another Count into this one, as Count += right.
     */
    inline Count& /// \returns this Count, the left side of Count += Count
    operator+=(
        const Count& right ///< The Count to add to this
    )
    {
        count += right.count;
        fails += right.fails;
        return *this;
    }
};

}
#endif