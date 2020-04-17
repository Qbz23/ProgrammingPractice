#include "TestRunner.h"
#include "../Logging/Logging.h"

static std::vector<std::pair<int(*)(), std::string>> m_Tests;
void TestRunner::RegisterTest(int(*pTestFx)() , std::string testName)
{
    m_Tests.push_back(std::make_pair(pTestFx, testName));
}

int TestRunner::RunAllTests()
{
    int numPassed = 0;
    for (auto it = m_Tests.begin(); it != m_Tests.end(); ++it)
    {
        Log::If(Log::bLogTests, it->second + "\n");

        int failedCases = it->first();
        if (failedCases > 0)
        {
            std::string errStr = it->second + ": Failed " + std::to_string(failedCases) + " Cases.\n\n";
            Log::If(Log::bLogTests, errStr);
        }
        else
        {
            Log::If(Log::bLogTestsVerbose, it->second + ": Passed All Cases.\n\n");
            numPassed += 1;
        }
    }

    std::string testResultStr = "Passed " + std::to_string(numPassed) + 
        " / " + std::to_string(m_Tests.size()) + " Tests.\n";
    Log::If(Log::bLogTests, testResultStr);

    return (int)m_Tests.size() - numPassed;
}
