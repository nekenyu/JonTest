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
verbose(verbose)
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
        out << "\t" << suiteName << ":" << caseName << ": start" <<"\n";
    }
}

void StreamLogger::errorCase(
    const std::string& suiteName,
    const std::string& caseName,
    const std::string& casePart,
    const std::string& message
)
{
    out << "\t" << suiteName << ":" << caseName << ": " << casePart
    << " " <<  message << "\n";
}

void StreamLogger::failCase(
    const std::string& suiteName,
    const std::string& caseName,
    const std::string& casePart,
    const TestFailure& failure
)
{
    out << "\t" << suiteName << ":" << caseName << ": " << casePart
        << " FAILED: " << failure.what() << "\n";
}

void StreamLogger::exceptionCase(
    const std::string& suiteName,
    const std::string& caseName,
    const std::string& casePart,
    const std::exception& unexpected
)
{
    out << "\t" << suiteName << ":" << caseName << ": " << casePart
        << " UNEXPECTED EXCEPTION: " << unexpected.what() << "\n";
}

void StreamLogger::endCase(
    const std::string& suiteName,
    const std::string& caseName,
    const bool pass
)
{
    if(verbose)
    {
        out << "\t" << suiteName << ":" << caseName << ": done " 
        << (pass ? "passed" : "FAILED") <<"\n";
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

void StreamLogger::end(
    const Count& count
)
{
    out << "Tests Complete:\t\tRun: " << count.count << "\t\tFails: " << count.fails << std::endl;
}

}