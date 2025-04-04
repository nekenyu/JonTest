#include "ExpectedFailureLogger.h"

#include "JonTest/Count.h"
#include "JonTest/Logger.h"
#include "JonTest/TestRunner.h"

#include <array>
#include <iostream>

namespace
{

/** Outputs help information for this program with optional error message.
 * 
 * /warning This program will NOT exit()... Caller must do so.
 * 
 * Always displays help information, naming "program" as a command line executable.
 * If error is not empty:
 * - States there was an error, including the error message
 * - If errorInfo is not empty:
 *   - Appends ": " and errorInfo to the error line
 */
void doHelp(
    const std::string& program, ///< The program executable name
    const std::string& error = std::string(""), ///< Non-empty error message string, otherwise ""
    const std::string& errorInfo = std::string("") ///< Non-empty error info message string, otherwise ""
)
{
    std::cout
        << program << " -- Run Unit Tests\n"
        << "\n"
        << "Runs the automatically build=defined unit tests.\n"
        << "\tExit code is number of failed tests, or 1 for program error.\n"
        << "\n"
        << "Arguments:\t\t(alias)\n"
        << "\t--help\t\t-h\tGets this help information\n"
        << "\t--verbose\t-v\tEnables verbose output\n"
        << "Note: aliases may NOT be concatenated, such as \"-hv\"\n\n";

    if(!error.empty())
    {
        std::cout << "Error: " << error;
        if(!errorInfo.empty())
        {
            std::cout << ": " << errorInfo;
        }
        std::cout << "\n";
   }
}

/** Returns true if argument is in matches, as determined by operator ==.
 * 
 * \tparam S Type of element in matches
 * \tparam T Type of value
 */
template<typename S, typename T, long unsigned int length>
bool /// Returns true if value operator == an item in matches, otherwise false
contains(
    std::array<S, length> matches, ///< to look for value in
    const T& value ///< to look for in matches
)
{
    for(auto const match : matches)
    {
        if(value == match)
        {
            return true;
        }
    }
    return false;
}

}

/** Example execution of JonTest via TestRunner::get().
 */
int /// \returns unix return code where 0 is success, positive values are the number of failed tests
main(
    int argc, ///< Number of arguments to program
    char**argv///< array of argc argument char* values to program
)
{
    bool verbose = false;
    {
        const std::string program(argv[0]);
        for(int i = 1; i < argc; ++i)
        {
            const std::string arg(argv[i]);
            if(contains(std::array{"--verbose", "-v"}, arg)) { verbose = true; }
            else if(contains(std::array{"--help", "-h"}, arg)) { doHelp(program); exit(0); }
            else { doHelp(program, "Unknown argument", arg.c_str()); exit(1); }
        }
    }

    ExpectedFailureLogger logger(std::cout, verbose);
    const JonTest::Count counts = JonTest::TestRunner::get().run(logger);
    const int fails = counts.fails - logger.getExpectedFailuresFailed();
    std::cout << "Tests Complete:\n" 
        << "\tRun: " << counts.count << "\t Fails: " << fails << std::endl;

    return fails;
}
