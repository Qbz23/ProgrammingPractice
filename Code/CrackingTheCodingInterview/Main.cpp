#include "CrackingTheCodingInterview.h"
#include "../Shared/Testing/TestRunner.h"
#include "../Shared/Logging/Logging.h"

int main(int argC, char** argV)
{
    // TODO
    // Maybe log from cmd line args in future but not right now
    //
    Log::Enable(Log::bLogTests);
    //Log::Enable(Log::bLogTestsVerbose);
    Log::Enable(Log::bLogTestCases);
    //Log::Enable(Log::bLogTestCasesVerbose);

    // Arrays and Strings
    TestRunner::RegisterTest(&Cci::Run_1_1, "1-1. Is Unique");
    TestRunner::RegisterTest(&Cci::Run_1_5, "1-5. One Away");
    TestRunner::RegisterTest(&Cci::Run_1_8, "1-8. Zero Matrix");
    TestRunner::RegisterTest(&Cci::Run_1_9, "1-9. Is Rotation");

    // Linked Lists 
    TestRunner::RegisterTest(&Cci::Run_2_2, "2-2. Kth to Last");
    TestRunner::RegisterTest(&Cci::Run_2_6, "2-6. Is Palindrome");

    // Stacks and Queues 
    TestRunner::RegisterTest(&Cci::Run_3_5, "3-5. Sort Stack");

    // Trees and Graphs 
    TestRunner::RegisterTest(&Cci::Run_4_3, "4-3. List of Depths");

    // Bit Manipulation
    TestRunner::RegisterTest(&Cci::Run_5_1, "5-1. Insertion");
    TestRunner::RegisterTest(&Cci::Run_5_6, "5-6. Bit Flip Conversion");

    if(argC > 1)
    {
        return TestRunner::RunTests(argV[1]);
    }
    else 
    {
        return TestRunner::RunAllTests();
    }
}
