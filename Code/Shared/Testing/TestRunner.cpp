#include "TestRunner.h"
#include "../Logging/Logging.h"
#include <unordered_map>

typedef std::pair<std::string, int(*)()> TestPair;

static std::string GetTestCode(std::string testFullName)
{
    int dotIndex = (int)testFullName.find(".");
    if(dotIndex == -1) 
    {   
        Log::Debug("Invalid testname " + testFullName + " passed to GetTestCode()\n");
        return "";
    }
    else 
    {
        return testFullName.substr(0, dotIndex);
    }
}

// index by number code ( like 1-1 ), store pair of function and testname
static std::unordered_map<std::string, TestPair> m_Tests;
void TestRunner::RegisterTest(int(*pTestFx)(), std::string testName)
{
    m_Tests[GetTestCode(testName)] = std::make_pair(testName, pTestFx);
}

static int RunTestImpl(TestPair* pTp)
{
    Log::If(Log::bLogTests, pTp->first + "\n");

    int failedCases = pTp->second();;
    if (failedCases > 0)
    {
        std::string errStr = pTp->first + ": Failed " + std::to_string(failedCases) + " Case.\n\n";
        Log::If(Log::bLogTests, errStr);
    }
    else
    {
        Log::If(Log::bLogTestsVerbose, pTp->first + ": Passed All Cases.\n\n");
    }

    return failedCases;
}

int TestRunner::RunAllTests()
{
    int numPassed = 0;
    for (auto it = m_Tests.begin(); it != m_Tests.end(); ++it)
    {
        numPassed += RunTestImpl(&(it->second)) == 0;
    }

    std::string testResultStr = "Passed " + std::to_string(numPassed) + 
        " / " + std::to_string(m_Tests.size()) + " Tests.\n";
    Log::If(Log::bLogTests, testResultStr);

    return (int)m_Tests.size() - numPassed;
}

int TestRunner::RunTest(std::string testCode)
{
    auto testIt = m_Tests.find(testCode);
    if(testIt == m_Tests.end())
    {
        Log::Always("Failed to find test case with code " + testCode + "\n");
        Log::Debug("Registered Tests:\n");
        for(auto it = m_Tests.begin(); it != m_Tests.end(); ++it)
        {
            std::string testName = it->second.first;
            std::string testCode = it->first;
            Log::Debug("\t" + testName + " [" + testCode + "]\n");
        }

        return -1;
    }
    else 
    {
        return RunTestImpl(&(testIt->second));
    }
}

