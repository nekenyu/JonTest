#include "JonTest/Count.h"
#include "JonTest/Logger.h"
#include "JonTest/TestRunner.h"

#include <iostream>

/** Example execution of JonTest via TestRunner::get().
 */
int /// \returns unix return code where 0 is success, positive values are the number of failed tests
main(
    int argc, ///< Number of arguments to program
    char**argv///< array of argc argument char* values to program
)
{
    JonTest::StreamLogger logger(std::cout, false);
    const JonTest::Count counts = JonTest::TestRunner::get().run(logger);
    return counts.fails;
}