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
    TestRunner::RegisterTest(&Cci::Run_1_2, "1-2. Check Palindrome");
    TestRunner::RegisterTest(&Cci::Run_1_3, "1-3. URLify");
    TestRunner::RegisterTest(&Cci::Run_1_5, "1-5. One Away");
    TestRunner::RegisterTest(&Cci::Run_1_6, "1-6. String Compression");
    TestRunner::RegisterTest(&Cci::Run_1_8, "1-8. Zero Matrix");
    TestRunner::RegisterTest(&Cci::Run_1_9, "1-9. Is Rotation");

    // Linked Lists 
    TestRunner::RegisterTest(&Cci::Run_2_1, "2-1. Remove Dupes");
    TestRunner::RegisterTest(&Cci::Run_2_2, "2-2. Kth to Last");
    TestRunner::RegisterTest(&Cci::Run_2_3, "2-3. Delete Middle");
    TestRunner::RegisterTest(&Cci::Run_2_4, "2-4. Partition");
    TestRunner::RegisterTest(&Cci::Run_2_5, "2-5. Sum Lists");
    TestRunner::RegisterTest(&Cci::Run_2_6, "2-6. Is Palindrome");
    TestRunner::RegisterTest(&Cci::Run_2_7, "2-7. Intersction");

    // Stacks and Queues 
    TestRunner::RegisterTest(&Cci::Run_3_1, "3-1. Array Multi Stack");
    TestRunner::RegisterTest(&Cci::Run_3_2, "3-2. Stack Min");
    TestRunner::RegisterTest(&Cci::Run_3_3, "3-3. Stack of Plates");
    TestRunner::RegisterTest(&Cci::Run_3_4, "3-4. Queue via Stacks");
    TestRunner::RegisterTest(&Cci::Run_3_5, "3-5. Sort Stack");
    TestRunner::RegisterTest(&Cci::Run_3_6, "3-6. Animal Shelter");

    // Trees and Graphs 
    TestRunner::RegisterTest(&Cci::Run_4_3, "4-3. List of Depths");

    // Bit Manipulation
    TestRunner::RegisterTest(&Cci::Run_5_1, "5-1. Insertion");
    TestRunner::RegisterTest(&Cci::Run_5_3, "5-3. Flip Bit to Win");
    TestRunner::RegisterTest(&Cci::Run_5_4, "5-4. Next Number");
    TestRunner::RegisterTest(&Cci::Run_5_6, "5-6. Bit Flip Conversion");
    TestRunner::RegisterTest(&Cci::Run_5_7, "5-7. Pairwise Swap");
    TestRunner::RegisterTest(&Cci::Run_5_8, "5-8. Draw Line");

    // Recursion and Dynamic Programming
    TestRunner::RegisterTest(&Cci::Run_8_3, "8-3. Magic Index");
    TestRunner::RegisterTest(&Cci::Run_8_4, "8-4. Power Set");

    if(argC > 1)
    {
        return TestRunner::RunTests(argV[1]);
    }
    else 
    {
        return TestRunner::RunAllTests();
    }
}
