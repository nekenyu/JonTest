#ifndef JON_TEST_TEST_SUITE_H
#define JON_TEST_TEST_SUITE_H

#include "JonTest/Count.h"
#include "JonTest/TestFailure.h"
#include "JonTest/TestRunner.h"

#include <iostream>
#include <map>
#include <string>

namespace JonTest
{

class TestCase;

class TestSuiteBase
{
protected:
    virtual void setup();
    virtual void teardown();

public:
    virtual ~TestSuiteBase();

    virtual Count run(std::ostream& out, bool verbose) = 0;
};

template <typename TestSuiteDerived>
class TestSuiteTyped : public TestSuiteBase
{
public:
    typedef TestSuiteDerived TestSuite;

private:
    typedef void (TestSuite::*Case)();

    class TestCase
    {
    private:
        void log(std::ostream& out, const std::string& part, const std::string& suiteName, const std::string& caseName)
        {
            out << "\t" << suiteName << " - " << caseName << ": " << part <<"\n";
        }        

        void fail(std::ostream& out, const std::string& part, const std::string& suiteName, const std::string& caseName, const char* const what)
        {
            out << "\t" << suiteName << " - " << caseName << ": " << part << " FAILED: " << what << "\n";
        }

    public:
        std::string name;
        TestSuite::Case testCase;
        TestCase() : name(), testCase(nullptr) { }
        TestCase(const char* const name, Case const testCase) : name(name), testCase(testCase) { }
        TestCase(const TestCase& right) = default;
        ~TestCase() { }

        bool run(TestSuite& suite, std::ostream& out, bool verbose)
        {
            if(verbose) { log(out, "start", suite.getName(), name); }
        
            if(nullptr == testCase)
            {
                fail(out, "start", suite.getName(), name, "MISSING (Internal Error)");
                return false;
            }
        
            bool setupPassed = false;
            try { suite.setup(); setupPassed = true; }
            catch(TestFailure& failure) { fail(out, "setup", suite.getName(), name, failure.what()); }
            catch(...)                  { fail(out, "setup", suite.getName(), name, "UNEXPECTED EXCEPTION"); }

            bool casePassed = false;
            if(setupPassed) {
                try { (suite.* testCase)(); casePassed = true; }
                catch(TestFailure& failure) { fail(out, "case", suite.getName(), name, failure.what()); }
                catch(...)                  { fail(out, "case", suite.getName(), name, "UNEXPECTED EXCEPTION"); }
                }
            
            bool teardownPassed = false;
            try { suite.teardown(); teardownPassed = true; }
            catch(TestFailure& failure) { fail(out, "teardown", suite.getName(), name, failure.what()); }
            catch(...)                  { fail(out, "teardown", suite.getName(), name, "UNEXPECTED EXCEPTION"); }
    
            const bool passed = setupPassed && casePassed && teardownPassed;
            if(verbose && passed) { log(out, "done", suite.getName(), name); }        
            return passed;
        }
    };

private:
    const std::string name;

    std::map<std::string, TestCase> cases;

public:
    class TestCaseHolder
    {
    private:
        TestCase testCase;
    public:
        inline TestCaseHolder(TestSuite& suite, const char* const name, TestSuite::Case const testCase)
        :testCase(name, testCase)
        {
            suite.add(name, testCase);
        }
    };

    TestSuiteTyped(const char * const name) : name(name) { TestRunner::get().add(name, this); }
    virtual ~TestSuiteTyped() { }

protected:
    void add(const char* const name, Case testCase) 
    {
        // TODO: Error check for overwrite
        cases[name] = TestCase(name, testCase);
    }

public:
    const std::string& getName() const { return name; }

    virtual Count run(std::ostream& out,bool verbose)
    {
        if(verbose)
        {
            out << "Beginning Suite: " << name << "\n";
        }
    
        Count counts;
        for(auto& nameCase : cases)
        {
            ++counts.count;
            const bool passed = nameCase.second.run(static_cast<TestSuite&>(*this), out, verbose);
            if(! passed)
            {
                ++counts.fails;
            }
        }
    
        if(verbose)
        {
            out << "Suite Complete: " << name << "\n"
                << "\tRun: " << counts.count << "\t Fails: " << counts.fails << "\n\n";
        }
        
        return counts;
    }
};


#define TEST_SUITE(name) \
namespace { \
class name : public JonTest::TestSuiteTyped<name> \
{ \
private: \
    typedef name SuiteName; \
public: \
    name() : TestSuiteTyped(#name) {}

#define TEST_SUITE_END() \
} test; \
}


#define TEST_CASE(name) \
TestSuite::TestCaseHolder name ##_holder = TestCaseHolder(*this, #name, &SuiteName::name); \
void name()

}

#endif