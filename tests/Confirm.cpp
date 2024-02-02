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