#ifndef COUNT_H
#define COUNT_H

#include <exception>
#include <ostream>

namespace JonTest
{

class Count
{
public:
    int count = 0;
    int fails = 0;

    inline Count& operator+=(const Count& right)
    {
        count += right.count;
        fails += right.fails;
        return *this;
    }
};

std::ostream& operator<<(std::ostream& stream, const Count& right);

// TODO: Move This
class TestFailure : public std::exception
{
    // TODO
};

}
#endif