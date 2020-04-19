#include "OtherTests.h"
#include "../Shared/Testing/TestRunner.h"
#include "../Shared/Logging/Logging.h"
#include "OtherTestsLogFlags.h"

int main(int argC, char** argV)
{
    Log::Enable(Log::bLogTests);
    //Log::Enable(Log::bLogTestsVerbose);
    Log::Enable(Log::bLogTestCases);
    //Log::Enable(Log::bLogTestCasesVerbose);
    //Log::Enable(OtherTestsLogFlags::LogDataStructureTestsVerbose);

    // Data Structure Tests
    TestRunner::RegisterTest(&OtherTests::BinaryTreeConstruct, "1-1 Binary Tree Construct");

    // Util Tests
    TestRunner::RegisterTest(&OtherTests::Tokenize, "2-1. Tokenize");
    TestRunner::RegisterTest(&OtherTests::WildcardMatch, "2-2. Wildcard Match");

    // Misc Tests
    TestRunner::RegisterTest(&OtherTests::BraceMatch, "3-1. Brace Match");

    //Log::Enable(Log::bLogNoisyObject);
    //Log::Enable(OtherTestsLogFlags::bLogExperiments);
    // Experiments 
    TestRunner::RegisterTest(&OtherTests::EmplaceTest, "4-1 Emplace Test");

    if (argC > 1)
    {
        return TestRunner::RunTests(argV[1]);
    }
    else
    {
        return TestRunner::RunAllTests();
    }
}
