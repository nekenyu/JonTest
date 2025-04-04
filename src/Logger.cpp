#include "JonTest/Logger.h"

#include "JonTest/TestFailure.h"

#include <ostream>
#include <string>

namespace JonTest
{

Logger::~Logger()
{
    // Nothing to do
}

StreamLogger::StreamLogger(
    std::ostream& out,
    bool verbose
)
:out(out),
verbose(verbose),
count()
{
}

StreamLogger::~StreamLogger()
{
    // Nothing to do
}

void StreamLogger::start()
{
    if(verbose)
    {
        out << "Beginning All Test Suites" << std::endl;
    }    
}

void StreamLogger::startSuite(
    const std::string& suiteName
)
{
    if(verbose)
    {
        out << "Beginning Suite: " << suiteName << "\n";
    }
}

void StreamLogger::startCase(
    const std::string& suiteName,
    const std::string& caseName
)
{
    if(verbose)
    {
        out << "\t" << suiteName << " - " << caseName << ": start" <<"\n";
    }

    // We will count the case only in endCase()
}

void StreamLogger::errorCase(
    const std::string& suiteName,
    const std::string& caseName,
    const std::string& casePart,
    const std::string& message
)
{
    out << "\t" << suiteName << " - " << caseName << ": " << casePart
    << " Internal Error: " << message << "\n";
}

void StreamLogger::failCase(
    const std::string& suiteName,
    const std::string& caseName,
    const std::string& casePart,
    const TestFailure& failure
)
{
    out << "\t" << suiteName << " - " << caseName << ": " << casePart
        << " FAILED: " << failure.what() << "\n";
}

void StreamLogger::endCase(
    const std::string& suiteName,
    const std::string& caseName,
    const bool pass
)
{
    if(verbose || !pass)
    {
        out << "\t" << suiteName << " - " << caseName << ": done " 
        << (pass ? "passed" : "FAILED") <<"\n";
    }

    ++count.count;
    if(!pass)
    {
        ++count.fails;
    }
}

void StreamLogger::endSuite(
    const std::string& suiteName,
    const Count& count
)
{
    if(verbose)
    {
        out << "Suite Complete: " << suiteName << "\n"
            << "\tRun: " << count.count << "\t Fails: " << count.fails << "\n\n";
    }
}

void StreamLogger::end()
{

    out << "Tests Complete:\n" 
        << "\tRun: " << count.count << "\t Fails: " << count.fails << std::endl;
}

Count StreamLogger::getCount() const
{
    return count;
}

}