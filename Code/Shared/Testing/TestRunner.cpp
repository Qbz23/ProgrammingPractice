#include "TestRunner.h"

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
#ifdef VERBOSE 
        std::cout << it->second << std::endl;
#endif 

        int failedCases = it->first();
        if (failedCases > 0)
        {
            std::cout << it->second << ": Failed " << std::to_string(failedCases) 
                << " Cases." << std::endl << std::endl;
        }
#ifdef VERBOSE
        else
        {
            std::cout << it->second << ": Passed All Cases." << std::endl << std::endl;
            numPassed += 1;
        }
#endif
    }

    std::cout << "Passed " + std::to_string(numPassed) << " / " <<
        std::to_string(m_Tests.size()) << " Tests." << std::endl;

    return (int)m_Tests.size() - numPassed;
}
