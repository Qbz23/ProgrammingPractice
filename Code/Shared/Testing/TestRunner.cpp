#include "TestRunner.h"
#include "../Logging/Logging.h"
#include <unordered_map>
#include "../Util/StringUtil.h"

// index by number code ( like 1-1 ), store pair of function and testname
static std::unordered_map<std::string, int(*)()> m_Tests;
void TestRunner::RegisterTest(int(*pTestFx)(), std::string testName)
{
    m_Tests[testName] = pTestFx;
}

static int RunTestImpl(int(*pTestFx)(), std::string testName)
{
    Log::If(Log::bLogTests, testName + "\n");

    int failedCases = pTestFx();;
    if (failedCases > 0)
    {
        std::string errStr = testName + ": Failed " + std::to_string(failedCases) + " Case(s).\n\n";
        Log::If(Log::bLogTests, errStr);
    }
    else
    {
        Log::If(Log::bLogTestsVerbose, testName + ": Passed All Case(s).\n\n");
    }

    return failedCases;
}

int TestRunner::RunAllTests()
{
    int numPassed = 0;
    for (auto it = m_Tests.begin(); it != m_Tests.end(); ++it)
    {
        numPassed += RunTestImpl(it->second, it->first) == 0;
    }

    std::string testResultStr = "Passed " + std::to_string(numPassed) + 
        " / " + std::to_string(m_Tests.size()) + " Tests.\n";
    Log::If(Log::bLogTests, testResultStr);

    return (int)m_Tests.size() - numPassed;
}

int TestRunner::RunTests(std::string testNameExpression)
{
    int numPassed = 0;
    int numRun = 0;
    for(auto it = m_Tests.begin(); it != m_Tests.end(); ++it)
    {
        if(Util::String::WildcardMatch(testNameExpression, it->first))
        {
            numPassed += RunTestImpl(it->second, it->first) == 0;
            numRun += 1;
        }
    }

    if(numRun == 0)
    {
        Log::Always("Failed to find test case from expression " + testNameExpression + "\n");
        Log::Debug("Registered Tests:\n");
        for (auto it = m_Tests.begin(); it != m_Tests.end(); ++it)
        {
            Log::Debug("\t" + it->first + "\n");
        }
    }
    else 
    {
        std::string testResultStr = "Passed " + std::to_string(numPassed) +
            " / " + std::to_string(numRun) + " Tests.\n";
        Log::If(Log::bLogTests, testResultStr);
    }

    return numRun - numPassed;
}

