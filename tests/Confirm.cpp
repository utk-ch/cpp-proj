#include "../Test.h"

bool isNegative(int num)
{
    return num < 0;
}

int multiplyBy2(int num)
{
    return num * 2;
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