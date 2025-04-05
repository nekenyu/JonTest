#include "JonTest/TestSuite.h"
#include "JonTest/Assert.h"

#include <cstring>
#include <iostream>
#include <string>

/** Example execution of JonTest showing a number of asserts and test cases.
 */
int /// \returns unix return code where 0 is success, positive values are the number of failed tests
main(
    int argc, ///< Number of arguments to program
    char**argv///< array of argc argument char* values to program
)
{
    JonTest::StreamLogger logger(std::cout, true);
    const JonTest::Count counts = JonTest::TestRunner::get().run(logger);
    return counts.fails;
}

TEST_SUITE(SimpleTest)

    const std::string initialString =  "This is a test string!";

    std::string testString;

    void setup()
    {
        testString = initialString;

        // NOTE: testing assert in setup()
        assertEqual(initialString, testString, "No change has been made");
    }

    void teardown()
    {
        testString.clear();

        // NOTICE: testing assert in teardown()
        assertEqual(0, testString.length(), "Length should be zero");
    }

    TEST_CASE(stringEqual)
    {
        // Duplicates test in setup()
        assertEqual(initialString, testString, "No change has been made");
    }

    TEST_CASE(stringClear)
    {
        testString.clear();
        assertEqual(std::string(), testString, "Should be empty string");

        // Duplicates test in teardown()
        assertEqual(0, testString.length(), "Length should be zero");

        // NOTICE: This compares a char string with a std::string
        assertEqual("", testString, "Should be empty string");
    }

    TEST_CASE(stringAssignCharEmpty)
    {
        testString = "";
        assertEqual(std::string(), testString, "Should be empty string");
        assertEqual(0, testString.length(), "Length should be zero");

        // NOTICE: This compares a char string with a std::string
        assertEqual("", testString, "Should be empty string");
    }

    TEST_CASE(stringAssignInitial)
    {
        testString = "";
        assertEqual(std::string(), testString, "Should be empty string");

        testString = initialString;
        assertEqual(initialString, testString, "Should match after assignment");
        assertEqual(strlen(initialString.c_str()), testString.length(), "Compare length against c string");
        assertEqual(strlen(initialString.c_str()), strlen(testString.c_str()), "Compare length of both as c strings");
        assertEqual(0, strncmp(initialString.c_str(), testString.c_str(), initialString.length()), "Compare both as c strings");

        // NOTICE: This compares a char string with a std::string
        assertEqual(initialString, testString.c_str(), "Should match as c string after assignment");
    }

TEST_SUITE_END();