#include "JonTest/TestFailure.h"

namespace JonTest
{
    
TestFailure::~TestFailure()
{
    // Nothing to do
}

const char* TestFailure::what() const noexcept
{
    return whatString.c_str();
}

}