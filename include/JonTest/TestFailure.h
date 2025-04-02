#ifndef JON_TEST_TEST_FAILURE_H
#define JON_TEST_TEST_FAILURE_H

#include <exception>
#include <string>
#include <sstream>

namespace JonTest
{

class TestFailure : public std::exception
{
public:
    std::string file;
    int line;
    std::string message;
    std::string whatString;
/*
    inline TestFailure(const char* const file, const int line, const std::string& message)
    :file(file), line(line), message(message) {
        std::ostringstream out;
        out << "At " << file << ": " << line << ": " << message;
        whatString = out.str();
    }
*/
    template<typename Type1, typename Type2>
    inline TestFailure(const char* const file, const int line, const std::string& message,
        const char* const firstString, const Type1& firstEval,
        const char* const secondString, const Type2& secondEval,
        const char* const operString)
    :file(file), line(line), message(message) {
        std::ostringstream out;
        out << "At " << file << ": " << line << ": " << message << "\n";        
        if(operString) {
            out << "\t\tTest:   first " << operString <<  " second\n"; 
            out << "\t\tFirst:  " << firstEval  << " = " << firstString <<  "\n"; 
            out << "\t\tSecond: " << secondEval << " = " << secondString << "\n";
        }
        whatString = out.str();
    }

    inline virtual ~TestFailure() { }
    inline virtual const char* what() const noexcept { return whatString.c_str(); }
};

}

#endif