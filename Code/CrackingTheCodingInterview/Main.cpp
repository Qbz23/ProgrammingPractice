#include "Tests.h"
#include "../Shared/Testing/TestRunner.h"
#include "../Shared/Logging/Logging.h"

// Todo 
//  emplacetest 
//  Fix noisy object to report counts rather than printing, print in verbose
//  Clean up includes

int main(int argC, char** argV)
{
    // TODO move cmdline handle to shared since 
    // testcode is assumed in the shared testrunner
    // Fix up this as well so it works like /name: and you can just regex
    // Can remove testcodes and just store name but still include testcodes 
    // at the beginning of names for organization and easier selection if you want 
    bool bRunAllTests = true;
    std::string testCode = "";
    if(argC > 1)
    { 
        // 0 is path
        std::string arg = argV[1];
        int dashIndex = (int)arg.find('-');
        if(dashIndex == -1)
        {
            Log::Always("Unrecognized argument " + arg + ", use format #-#\n");
            return -1;
        }
        else 
        {
            try
            {
                // Unecessary conversion but is a form of validation
                int num1 = std::stoi(arg.substr(0, dashIndex));
                int num2 = std::stoi(arg.substr(dashIndex + 1));
                testCode = std::to_string(num1) + "-" + std::to_string(num2);
                bRunAllTests = false;
            }
            catch(std::exception e)
            {
                Log::Always("Failed to interpret arg " + arg + " as test code:\n");
                Log::Always(e.what());
                return -2;
            }            
        }
    }

    //
    // TODO
    // Maybe log from cmd line args in future but not right now
    //
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

    if(bRunAllTests)
    {
        return TestRunner::RunAllTests();
    }
    else 
    {
        return TestRunner::RunTest(testCode);        
    }
}