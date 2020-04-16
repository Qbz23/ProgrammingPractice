#include "Tests.h"
#include "../Shared/Testing/TestRunner.h"

int main()
{
    TestRunner::RegisterTest(std::make_pair(&Tests::Run_1_1, "1-1. Is Unique"));
    TestRunner::RegisterTest(std::make_pair(&Tests::Run_1_5, "1-5. Is Unique"));

    TestRunner::RunAllTests();
}