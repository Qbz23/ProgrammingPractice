#pragma once

#include <iostream>
#include <vector>
#include <string>

// todo log verbose functio ninstead compile to noop if verbose not defined, 1 ifdef
#define VERBOSE

namespace testRunner
{
    template<typename ParamType, typename ReturnType>
    struct TestData
    {
        public:
            TestData(ParamType p, ReturnType r) : input(p), expectedOutput(r) {};
            ParamType input;
            ReturnType expectedOutput;
    };

    static std::vector<std::pair<int(*)(), std::string>> m_Tests;
    void RegisterTest(std::pair<int(*)(), std::string> test)
    {
        m_Tests.push_back(test);
    }

    void RunAllTests()
    {
        int numPassed = 0;
        for(auto it = m_Tests.begin(); it != m_Tests.end(); ++it)
        {
#ifdef VERBOSE 
            std::cout << it->second << std::endl;
#endif 

            int failedCases = it->first();
            if(failedCases > 0)
            {
                std::cout << it->second << ": Failed " << std::to_string(failedCases) << " Cases." << std::endl;
            }
#ifdef VERBOSE
            else 
            {
                std::cout << it->second << ": Passed All Cases." << std::endl;
                numPassed += 1; 
            }
#endif
        }

        std::cout << "Passed " + std::to_string(numPassed) << " / " <<
        std::to_string(m_Tests.size()) << " Tests." << std::endl;
    }

    template<typename ParamType, typename ReturnType, unsigned int numTests>
    int runTests(TestData<ParamType, ReturnType> testData[numTests], ReturnType (*pFunction)(ParamType& p))
    {
        int failed = 0;
        for(unsigned int i = 0; i < numTests; ++i)
        {
            TestData<ParamType, ReturnType>& td = testData[i];
            ReturnType result = (*pFunction)(td.input);
            if(result != td.expectedOutput)
            {   
                failed += 1;
#ifdef VERBOSE
                std::cout << "Failed case " << i << ". Expected " <<
                    td.expectedOutput << " but got " << result << std::endl;
#endif // VERBOSE
            }
        }

#ifdef VERBOSE
        std::cout << "Passed " << numTests - failed << " / " << numTests << " test cases." << std::endl;
#endif // VERBOSE
        return failed;
    }
    
    template<typename r>
    std::ostream& operator<<(std::ostream& os, std::vector<r> td)
    {
        for(auto it = td.begin(); it != td.end(); ++it)
        {
            os << *it << std::endl;
        }
        
        return os;
    }
}



#define DEF_TESTDATA(name, inputType, outputType) struct name : public testRunner::TestData<inputType, outputType> \
{ \
    name(inputType p, outputType r) : TestData(p, r) {} \
}; 
    