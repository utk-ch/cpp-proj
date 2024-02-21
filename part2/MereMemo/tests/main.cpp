/*instead of #include "Test.h" we are using
#include <MereTDD/Test.h> because it is part
of different project
 */
#include "../../MereTDD/Test.h"
#include <iostream>
int main()
{
    return MereTDD::runTests(std::cout);
}