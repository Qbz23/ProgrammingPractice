#pragma once 

#include <iostream>
#include <vector>
#include <string>

// todo log verbose functio ninstead compile to noop if verbose not defined, 1 ifdef
#define VERBOSE

namespace TestRunner
{
    extern void RegisterTest(int(*pTestFx)(), std::string testName);
    extern int RunAllTests();

    template<typename ParamType, typename ReturnType>
    struct TestData
    {
        public:
            TestData(ParamType p, ReturnType r) : input(p), expectedOutput(r) {};
            ParamType input;
            ReturnType expectedOutput;
    };

    template<typename ParamType, typename ReturnType, unsigned int numTests>
    int RunTestCases(TestData<ParamType, ReturnType> testData[numTests], ReturnType (*pFunction)(ParamType& p))
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
}

template<typename r>
std::ostream& operator<<(std::ostream& os, std::vector<r> td)
{
    for (auto it = td.begin(); it != td.end(); ++it)
    {
        os << *it << std::endl;
    }

    return os;
}



#define DEF_TESTDATA(name, inputType, outputType) struct name : public TestRunner::TestData<inputType, outputType> \
{ \
    name(inputType p, outputType r) : TestData(p, r) {} \
}; 
    