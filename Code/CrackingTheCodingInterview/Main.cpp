#include "../Shared/Testing/TestRunner.hpp"

#include "1-ArraysAndStrings/1-1.hpp"

int main()
{
    testRunner::RegisterTest(std::make_pair(&IsUnique_1_1, "Is Unique 1-1"));

    testRunner::RunAllTests();
}