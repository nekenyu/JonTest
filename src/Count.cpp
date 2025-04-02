#include "JonTest/Count.h"

#include <iostream>

namespace JonTest
{
std::ostream& operator<<(std::ostream& stream, const Count& right)
{
    stream << "Count: " << right.count << "\tFails: " << right.fails;
    return stream;
}

}