#include "Tests.h"
#include "../Shared/Testing/TestRunner.h"
#include "../Shared/Logging/Logging.h"


int main(int argC, char** argV)
{
    Log::Enable(Log::bLogTests);
    //Log::Enable(Log::bLogTestsVerbose);
    Log::Enable(Log::bLogTestCases);
    //Log::Enable(Log::bLogTestCasesVerbose);

    // Util Tests
    TestRunner::RegisterTest(&Tests::Tokenize, "1-1. Tokenize");
    TestRunner::RegisterTest(&Tests::WildcardMatch, "1-2. Wildcard Match");

    // Other
    TestRunner::RegisterTest(&Tests::BraceMatch, "2-1. Brace Match");

    if (argC > 1)
    {
        return TestRunner::RunTests(argV[1]);
    }
    else
    {
        return TestRunner::RunAllTests();
    }
}
