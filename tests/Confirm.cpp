#include "../Test.h"

bool isNegative(int num)
{
    return num < 0;
}

int multiplyBy2(int num)
{
    return num * 2;
}

long multiplyBy2 (long value)
{
    return value * 2L;
}

long long multiplyBy2 (long long value)
{
    return value * 2LL;
}

TEST("Test will pass without any confirms")
{
   
}

TEST("Test int confirms")
{
    int result = multiplyBy2(0);
    CONFIRM(0, result);

    result = multiplyBy2(1);
    CONFIRM(2, result);

    result = multiplyBy2(-1);
    CONFIRM(-2, result);
}

TEST("Test bool confirms")
{
    bool result = isNegative(0);

    CONFIRM_FALSE(result);

    result = isNegative(-1);

    CONFIRM_TRUE(result);
}

TEST("Test bool confirm failure")
{
    std::string reason = "   Expected: true";
    setExpectedFailureReason(reason);

    bool result = isNegative(0);

    CONFIRM_TRUE(result);
}

TEST("Test int confirm failure")
{
    std::string reason = "   Expected: 1\n";
    reason += "   Actual: 2";
    setExpectedFailureReason(reason);

    int result = multiplyBy2(1);
    CONFIRM(1, result);
}

TEST("Test long confirms")
{
    long result = multiplyBy2(0L);
    CONFIRM(0L, result);

    result = multiplyBy2(1L);
    CONFIRM(2L, result);

    result = multiplyBy2(-1L);
    CONFIRM(-2L, result);
}

TEST("Test long confirm failure")
{
    std::string reason = "   Expected: 0\n";
    reason += "   Actual: 2";
    setExpectedFailureReason(reason);

    long result = multiplyBy2(1L);
    CONFIRM(0L, result);
}


TEST("Test long long confirms")
{
    long long result = multiplyBy2(0LL);
    CONFIRM(0LL, result);

    result = multiplyBy2(10'000'000'000LL);
    CONFIRM(20'000'000'000LL, result);

    result = multiplyBy2(-10'000'000'000LL);
    CONFIRM(-20'000'000'000LL, result);
}

TEST("Test long long confirm failure")
{
    std::string reason = "   Expected: 10000000000\n";
    reason += "   Actual: 20000000000";
    setExpectedFailureReason(reason);

    long long result = multiplyBy2(10'000'000'000LL);
    CONFIRM(10'000'000'000LL, result);
}