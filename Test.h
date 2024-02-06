#ifndef MERETDD_TEST_H

#define MERETDD_TEST_H

#include <ostream>
#include <string_view>
#include <vector>

namespace MereTDD
{
    class ConfirmException
    {
        public:
            // ConfirmException() = default;
            ConfirmException (int line): mLine(line) {}
            virtual ~ConfirmException() = default;
            std::string_view reason() const
            {
                return mReason;
            }
            int line() const
            {
                return mLine;
            }
        protected:
            std::string mReason;
            int mLine;
    };

    class BoolConfirmException : public ConfirmException
    {
        public:
            BoolConfirmException(bool expected, int line) : ConfirmException(line)
            {
                mReason += "   Expected: ";
                mReason += expected ? "true" : "false";
            }
    };

    class ActualConfirmException : public ConfirmException
    {
        public:
            ActualConfirmException(
                std::string_view expected, 
                std::string_view actual, 
                int line
            ) 
                : ConfirmException(line), 
                mExpected(expected), 
                mActual(actual)
            {
                formatReason();
            }
        private:
            void formatReason()
            {
                mReason += "   Expected: " + mExpected + "\n";
                mReason += "   Actual: " + mActual;
            }
            std::string mExpected;
            std::string mActual;
    };

    class MissingException
    {
    public:
        MissingException(std::string_view exType) : mExType(exType)
        {
        }
        std::string_view exType() const
        {
            return mExType;
        }

    private:
        std::string mExType;
    };
    inline void confirm(bool expected, bool actual, int line)
    {
        if (actual != expected)
        {
            throw BoolConfirmException(expected, line);
        }
    }
    /*
    inline void confirm(int expected, int actual, int line)
    {
        if (actual != expected)
        {
            throw ActualConfirmException(expected, actual, line);
        }
    }
    */
    template <typename T>
    void confirm(T const& expected, T const& actual, int line)
    {
        if (actual != expected)
        {
            throw ActualConfirmException(
                std::to_string(expected), 
                std::to_string(actual), 
                line);
        }
    }
    class TestBase
    {
    public:
        TestBase(std::string_view name) : mName(name), mPassed(true), mConfirmLocation(-1)
        {
        }
        virtual ~TestBase() = default;
        virtual void runEx()
        {
            run();
        }
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
        void set_failed(std::string_view reason, int confirmLocation = -1)
        {
            mPassed = false;
            mReason = reason;
            mConfirmLocation = confirmLocation;
        }
        void setExpectedFailureReason(std::string_view reason)
        {
            mExpectedReason = reason;
        }
        std::string_view expectedReason() const
        {
            return mExpectedReason;
        }
        int confirmLocation() const
        {
            return mConfirmLocation;
        }

    private:
        std::string mName;
        bool mPassed;
        std::string mReason;
        std::string mExpectedReason;
        int mConfirmLocation;
    };

    // defines a collection of tests to be run

    inline std::vector<TestBase *> &getTests()
    {
        // make sure the vector is initialized only once
        // no matter how many times this function is called
        static std::vector<TestBase *> tests;
        return tests;
    }
    inline int runTests(std::ostream &output)
    {
        // core logic to run tests should be handled here and not in main.cpp
        output << "Running " << getTests().size() << " tests" << std::endl;

        int numPassed = 0;
        int numMissedFailure = 0;
        int numFailed = 0;

        for (auto *test : getTests())
        {
            output << "-----------\nRunning test: " << test->name() << std::endl;
            try
            {
                test->runEx();
            }
            catch (ConfirmException const &ex)
            {
                test->set_failed(ex.reason(), ex.line());
            }
            catch (MissingException const &ex)
            {
                std::string message = "Expected exception type ";
                message += ex.exType();
                message += " was not thrown.";
                test->set_failed(message);
            }
            catch (...)
            {
                test->set_failed("Unexpected exception thrown.");
            }

            if (test->passed())
            {
                if (not test->expectedReason().empty())
                {
                    // test was expected to fail but did not
                    ++numMissedFailure;
                    output << "Missed expected failure\n"
                           << "Test passed but was expected to fail."
                           << std::endl;
                }
                else
                {
                    ++numPassed;
                    output << "Test passed" << std::endl;
                }
            }
            else if (not test->expectedReason().empty() &&
                     test->expectedReason() == test->reason())
            {
                // test was expected to fail and did with the expected reason
                ++numPassed;
                output << "Test failed as expected: " << test->reason() << std::endl;
            }
            else
            {
                ++numFailed;
                if (test->confirmLocation() != -1)
                {
                    output << "Failed confirm on line " << test->confirmLocation() << std::endl;
                }
                else
                {
                    output << "Failed" << std::endl;
                }
                output << test->reason() << std::endl;
            }
        }
        output << "-----------\n";
        output << "Test passed: " << numPassed
               << "\nTests failed: " << numFailed;
        if (numMissedFailure != 0)
        {
            output << "\nTests failures missed: " << numMissedFailure;
        }

        // flush the output stream to make sure the output is written
        output << std::endl;

        return numFailed;
    }
} // namespace MereTDD

// macro definition stays outside of the namespace
// since the code is inserted where ever the macro is used
#define MERETDD_CLASS_FINAL( line ) Test ## line
#define MERETDD_CLASS_RELAY( line ) MERETDD_CLASS_FINAL( line )
#define MERETDD_CLASS MERETDD_CLASS_RELAY( __LINE__ )

#define MERETDD_INSTANCE_FINAL( line ) test ## line
#define MERETDD_INSTANCE_RELAY( line ) MERETDD_INSTANCE_FINAL( line )
#define MERETDD_INSTANCE MERETDD_INSTANCE_RELAY( __LINE__ )

#define TEST(testName) \
namespace { \
class MERETDD_CLASS : public MereTDD::TestBase \
{ \
public: \
    MERETDD_CLASS (std::string_view name) \
    : TestBase(name) \
    { \
        MereTDD::getTests().push_back(this); \
    } \
    void run() override; \
}; \
} /* end of unnamed namespace, this allows for using same Test name across multiple cpp files*/ \
MERETDD_CLASS MERETDD_INSTANCE(testName); \
void MERETDD_CLASS::run()

#define TEST_EX(testName, exceptionType) \
namespace { \
class MERETDD_CLASS : public MereTDD::TestBase \
{ \
public: \
    MERETDD_CLASS (std::string_view name) \
    : TestBase(name) \
    { \
        MereTDD::getTests().push_back(this); \
    } \
    void runEx () override \
    { \
        try \
        { \
            run(); \
        } \
        catch (exceptionType const &) \
        { \
            return; \
        } \
        throw MereTDD::MissingException(#exceptionType); \
    } \
    void run() override; \
}; \
} /* end of unnamed namespace, this allows for using same Test name across multiple cpp files*/ \
MERETDD_CLASS MERETDD_INSTANCE(testName); \
void MERETDD_CLASS::run()

#define CONFIRM_FALSE(actual) \
    MereTDD::confirm(false, actual, __LINE__)

#define CONFIRM_TRUE(actual) \
    MereTDD::confirm(true, actual, __LINE__)

#define CONFIRM(expected, actual) \
    MereTDD::confirm(expected, actual, __LINE__)

#endif // TEST_H
