#include "Tests.h"
#include "../Shared/Testing/TestRunner.h"
#include "../Shared/Logging/Logging.h"


int main()
{
    Log::Enable(Log::bLogTests);
    //Log::Enable(Log::bLogTestsVerbose);
    Log::Enable(Log::bLogTestCases);
    //Log::Enable(Log::bLogTestCasesVerbose);

    // placeholder test code for now. 
    TestRunner::RegisterTest(&Tests::BraceMatch, "1-1. Brace Match");
    return TestRunner::RunAllTests();
}
