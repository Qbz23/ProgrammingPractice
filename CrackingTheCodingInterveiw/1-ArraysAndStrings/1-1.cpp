// 1.1 Is Unique - pg90

// determine if string has all unique characters
// How to solve if no extra data?

#include "../../Shared/TestRunner.hpp"
#include <string>
#include <iostream>

DEF_TESTDATA(IsUniqueData, std::string, bool) 

// O(n)
bool isUnique(std::string s)
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
bool isUniqueNoAdditionalData(std::string s)
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

int main()
{
    const unsigned int kNumTestCases = 5;
    IsUniqueData testCases[kNumTestCases] = {
        {"aabb",        false}, 
        {"abcd",        true},
        {"12ab!5d",     true},
        {"",            true},
        {"abc123!@#a",  false}};
    
    std::cout << "Basic" << std::endl;
    testRunner::runTests<std::string, bool, kNumTestCases>(testCases, &isUnique);
    std::cout << "No Additional Data" << std::endl;
    testRunner::runTests<std::string, bool, kNumTestCases>(testCases, &isUniqueNoAdditionalData);
}