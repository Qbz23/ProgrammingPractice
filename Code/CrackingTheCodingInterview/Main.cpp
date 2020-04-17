#include "Tests.h"
#include "../Shared/Testing/TestRunner.h"
#include "../Shared/Logging/Logging.h"

// Todo 
//  add cmd line parse to run specific case 
//  Make other project for other exes, emplacetest and bracematch
//  Fix noisy object to report counts rather than printing, print in verbose

int main()
{
    Log::Enable(Log::bLogTests);
    //Log::Enable(Log::bLogTestsVerbose);
    Log::Enable(Log::bLogTestCases);
    //Log::Enable(Log::bLogTestCasesVerbose);

    // Arrays and Strings
    TestRunner::RegisterTest(&Tests::Run_1_1, "1-1. Is Unique");
    TestRunner::RegisterTest(&Tests::Run_1_5, "1-5. One Away");
    TestRunner::RegisterTest(&Tests::Run_1_8, "1-8. Zero Matrix");

    // Linked Lists 
    TestRunner::RegisterTest(&Tests::Run_2_2, "2-2. Kth to Last");

    // Stacks and Queues 
    TestRunner::RegisterTest(&Tests::Run_3_5, "3-5. Sort Stack");

    // Trees and Graphs 
    TestRunner::RegisterTest(&Tests::Run_4_3, "4-3. List of Depths");

    // Bit Manipulation
    TestRunner::RegisterTest(&Tests::Run_5_6, "5-6. Bit Flip Conversion");


    return TestRunner::RunAllTests();
}