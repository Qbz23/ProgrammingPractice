#include "TestRunner.h"

static std::vector<std::pair<int(*)(), std::string>> m_Tests;
void TestRunner::RegisterTest(std::pair<int(*)(), std::string> test)
{
    m_Tests.push_back(test);
}

void TestRunner::RunAllTests()
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
}
