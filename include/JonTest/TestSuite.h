#ifndef TEST_SUITE_H
#define TEST_SUITE_H

#include "JonTest/Count.h"
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
    public:
        std::string name;
        TestSuite::Case testCase;
        TestCase() : name(), testCase(nullptr) { }
        TestCase(const char* const name, Case const testCase) : name(name), testCase(testCase) { }
        TestCase(const TestCase& right) = default;
        ~TestCase() { }

        bool run(TestSuite& suite, std::ostream& out, bool verbose)
        {
            if(verbose)
            {
                out << "Beginning Case: " << name << std::endl;
            }
        
            if(nullptr == testCase)
            {
                out << "Case FAILED: " << name << " MISSING (Internal Error)" << std::endl;
                return false;
            }
        
            bool passed = false;
            try
            {
                suite.setup();
                (suite.* testCase)();
                suite.teardown();
        
                passed = true;
                if(verbose)
                {
                    out << "Case Complete: " << name << std::endl;
                }
            }
            catch(TestFailure& failure)
            {
                out << "Case FAILED: " << name << std::endl;
            }
            catch(...)
            {
                out << "Case FAILED: " << name << " UNEXPECTED" << std::endl;
            }
        
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
    virtual Count run(std::ostream& out,bool verbose)
    {
        if(verbose)
        {
            out << "Beginning Suite: " << name << std::endl;
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
            out << "Suite Complete: " << name << std::endl
                << "\tRun: " << counts.count << "\t Fails: " << counts.fails << std::endl;
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