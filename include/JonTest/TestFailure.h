#ifndef JON_TEST_TEST_FAILURE_H
#define JON_TEST_TEST_FAILURE_H

#include <exception>
#include <string>
#include <sstream>

namespace JonTest
{

/** Exception thrown when a test fails an assert and should fail (unless wrapped in expectedFailure()).
 *
 * Contains all test data from failure.
*/
class TestFailure : public std::exception
{
public:
    /// Filename where failure occurred
    std::string file;

    /// Line number of file where failure occurred
    int line;

    /// Message provided where failure occurred
    std::string message;

    /// String representation of first expression that failed the test
    std::string firstExpression;

    /// String representation of evaluation of first expression that failed the test
    std::string firstValue;

    /// String representation of second expression that failed the test
    std::string secondExpression;

    /// String representation of evaluation of second expression that failed the test
    std::string secondValue;

    /// String representation of operator that failed the test
    std::string operatorString;

    /// Formatted representation of  failure
    std::string whatString;

    /** Construct Test Failure Exception.
     * 
     * \note Relies on operator<< for Type1 and Type2.
     * 
     * \tparam Type1 Type which first expression evaluated to
     * \tparam Type2 Type which second expression evaluated to
     */
    template<typename Type1, typename Type2>
    inline TestFailure(
        const char* const file, ///< Filename where failure occurred
        const int line, ///< Line number of file where failure occurred
        const std::string& message, ///< Message provided where failure occurred
        const char* const firstExpression, ///< String representation of first expression that failed the test
        const Type1& firstValue, ///< Evaluation of the first expression that failed the test
        const char* const secondExpression, ///< String representation of evaluation of second expression that failed the test
        const Type2& secondValue, ///< Evaluation of the second expression that failed the test
        const char* const operatorString ///< /// String representation of operator that failed the test
        )
    :file(file),
    line(line),
    message(message),
    firstExpression(firstExpression),
    secondExpression(firstExpression),
    operatorString(operatorString)
    {
        {
            std::ostringstream out;
            out << firstValue;
            this->firstValue = out.str();
        }

        {
            std::ostringstream out;
            out << secondValue;
            this->secondValue = out.str();
        }

        {
            std::ostringstream out;
            out << message << "\n\t\tAt " << file << ":" << line;
            if(!this->operatorString.empty()) {
                out << "\n\t\tExpression: " << firstExpression << " " << operatorString << " " << secondExpression << "\n";
                out << "\t\tValue: " << firstValue   << " " << operatorString << " " << secondValue;
            }
            whatString = out.str();
        }
    }

    /// Required virutal destructor
    virtual ~TestFailure();

    /** Gets formatted message of string
    * @returns formatted message of string 
    */
    virtual const char* what() const noexcept;
};

}

#endif