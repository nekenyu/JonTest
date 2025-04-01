// NOTICE: This is NOT a C++20 modules enabled project or build. This is generic "Module".
#include "ModulesTest.h"

#include "Example/Example.h"

namespace ModulesTest
{
    int getAnswer()
    {
        return Example::f();
    }
}