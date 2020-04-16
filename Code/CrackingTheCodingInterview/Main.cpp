#include "Tests.h"
#include "../Shared/Testing/TestRunner.h"

int main()
{
    // Arrays and Strings
    TestRunner::RegisterTest(std::make_pair(&Tests::Run_1_1, "1-1. Is Unique"));
    TestRunner::RegisterTest(std::make_pair(&Tests::Run_1_5, "1-5. Is Unique"));
    TestRunner::RegisterTest(std::make_pair(&Tests::Run_1_8, "1-8. Zero Matrix"));

    // Linked Lists 
    TestRunner::RegisterTest(std::make_pair(&Tests::Run_2_2, "2-2. Kth to Last"));

    // Stacks and Queues 
    
    // Trees and Graphs 

    // Bit Manipulation


    TestRunner::RunAllTests();
}