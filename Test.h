#ifndef MERETDD_TEST_H

#define MERETDD_TEST_H

#include <ostream>
#include <string_view>
#include <vector>

namespace mereTDD
{
    class TestBase
    {
        public:
            TestBase(std::string_view name) : mName(name), mPassed(true)
            {}
            virtual ~TestBase() = default;
            virtual void run() = 0;
            std::string_view name() const
            {
                return mName;
            }
            bool passed() const
            {
                return mPassed;
            }
            std::string_view reason() const
            {
                return mReason;
            }
            void set_failed(std::string_view reason)
            {
                mPassed = false;
                mReason = reason;
            }
        private:
            std::string mName;
            bool mPassed;
            std::string mReason;
    };
    
    // defines a collection of tests to be run

    inline std::vector<TestBase*>& getTests()
    {
        // make sure the vector is initialized only once
        // no matter how many times this function is called
        static std::vector<TestBase*> tests;
        return tests;
    }
    inline int runTests(std::ostream & output)
    {
        // core logic to run tests should be handled here and not in main.cpp
        output << "Running " << getTests().size() << " tests" << std::endl;

        int numPassed = 0;
        int numFailed = 0;

        for (auto *test : getTests())
        {
            output << "-----------\nRunning test: " << test->name() << std::endl;
            try
            {
                test->run();
            }
            catch(...)
            {
                test->set_failed("Exception thrown");
            }
            if (test->passed())
            {
                ++numPassed;
                output << "Test passed" << std::endl;
            }
            else
            {
                ++numFailed;
                output << "Test failed: " << test->reason() << std::endl;
            }
        }
        output << "-----------\n";
        if (numFailed == 0)
        {
            output << "All tests passed" << std::endl;
        }
        else
        {
            output << numPassed << " tests passed, " << numFailed << " tests failed" << std::endl;
        }

        return numFailed;
    }
} // namespace mereTDD

// macro definition stays outside of the namespace
// since the code is inserted where ever the macro is used
#define MERETDD_CLASS_FINAL( line ) Test ## line
#define MERETDD_CLASS_RELAY( line ) MERETDD_CLASS_FINAL( line )
#define MERETDD_CLASS MERETDD_CLASS_RELAY( __LINE__ )

#define MERETDD_INSTANCE_FINAL( line ) test ## line
#define MERETDD_INSTANCE_RELAY( line ) MERETDD_INSTANCE_FINAL( line )
#define MERETDD_INSTANCE MERETDD_INSTANCE_RELAY( __LINE__ )

#define TEST(testName) \
class MERETDD_CLASS: public mereTDD::TestBase \
{ \
    public: \
        MERETDD_CLASS (std::string_view name) \
        : TestBase(name) \
        { \
            mereTDD::getTests().push_back(this); \
        } \
        void run() override; \
}; \
MERETDD_CLASS MERETDD_INSTANCE(testName); \
void MERETDD_CLASS::run()

#endif // TEST_H
