#include "../Test.h"

bool isPassingGrade(int grade)
{
    return grade >= 70;
}

TEST("Test will pass without any confirms")
{
   
}

TEST("Test passing grades")
{
    bool result = isPassingGrade(0);

    CONFIRM_FALSE(result);

    result = isPassingGrade(0);

    CONFIRM_TRUE(result);
}