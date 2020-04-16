// 1.1 Is Unique - pg90

// determine if string has all unique characters
// How to solve if no extra data?

#include "../../Shared/Testing/TestRunner.h"
#include "../Tests.h"
#include <string>
#include <iostream>

namespace Cci_1_1
{
    DEF_TESTDATA(IsUniqueData, std::string, bool) 

    // O(n)
    bool IsUnique(std::string& s)
    {
        const unsigned int kNumAscii = 256;
        bool charFound[kNumAscii] = { false };  
        for(auto it = s.begin(); it != s.end(); ++it)
        {
            if(charFound[*it])
            {
                return false;
            }
            else
            {
                charFound[*it] = true;
            }
        }
    
        return true;
    }

    // O(n^2)
    bool IsUniqueNoAdditionalData(std::string& s)
    {
        for(size_t i = 0; i < s.length(); ++i)
        {
            for(size_t j = i + 1; j < s.length(); ++j)
            {
                if(s[i] == s[j])
                {
                    return false;
                }
            }
        }
    
        return true;
    }
};

int Tests::Run_1_1()
{
    const unsigned int kNumTestCases = 5;
    Cci_1_1::IsUniqueData testCases[kNumTestCases] = {
        {"aabb",        false}, 
        {"abcd",        true},
        {"12ab!5d",     true},
        {"",            true},
        {"abc123!@#a",  false}};
    
    int failedCases = 0;
    // Basic
    failedCases += TestRunner::RunTestCases<std::string, bool, kNumTestCases>(testCases, &Cci_1_1::IsUnique);
    // No additional data
    failedCases += TestRunner::RunTestCases<std::string, bool, kNumTestCases>(testCases, &Cci_1_1::IsUniqueNoAdditionalData);

    return failedCases;
}

