// 1.2 Check Permutation - pg90

// Given two strings, determine a method to decide if one is permutation of other 

#include "../../Shared/Testing/TestRunner.h"
#include "../CrackingTheCodingInterview.h"
#include <string>
#include <iostream>
#include <cassert>

struct StringPermutationInputData
{
    std::string s1;
    std::string s2;
};

DEF_TESTDATA(CheckPermutationData, StringPermutationInputData, bool)

static unsigned int GetIndex(char c, unsigned int rangeStart, unsigned int rangeEnd)
{
    assert((unsigned int)c >= rangeStart && (unsigned int)c <= rangeEnd);
    return (unsigned int)c - rangeStart;
}

static bool CheckPermutation(StringPermutationInputData& input)
{
    // Can't be permutation if different length
    if(input.s1.length() != input.s2.length())
    {
        return false;
    }

    // Loop over first string, count up each letter usage 
    const unsigned int rangeStart = 32;
    const unsigned int rangeEnd = 127;
    const unsigned int numLetters = rangeEnd - rangeStart;
    unsigned int letterCounts[numLetters] = { 0 };
    for(auto s1It = input.s1.begin(); s1It != input.s1.end(); ++s1It)
    {
        letterCounts[GetIndex(*s1It, rangeStart, rangeEnd)] += 1;
    }

    // Loop over second string, count down each letter usage 
    for (auto s2It = input.s2.begin(); s2It != input.s2.end(); ++s2It)
    {
        unsigned int index = GetIndex(*s2It, rangeStart, rangeEnd);
        if(letterCounts[index] > 0)
        {
            letterCounts[index] -= 1;
        }
        // The second string needed a letter the first string didn't have
        // therefore not a permutation. Don't need to worry about the case 
        // where there are letters remaining at the end because at this 
        // point, the strings must be the same length
        else 
        {
            return false;
        }
    }

    return true;
}

int Cci::Run_1_2()
{
    const unsigned int kNumTestCases = 11;
    // Book specifies no rules as to case, I'm going to treat case as different 
    CheckPermutationData testCases[kNumTestCases] = {
        {{"aabb",   "bbaa"},        true},
        {{"aabba",  "bbaa"},        false}, 
        {{"aabB",   "bbaa"},        false},
        {{"",       ""},            true},
        {{"%#$#@",   "@#$%#"},      true},
        {{"%#$#@",   "@#$%$"},      false},
        {{"abCdef",  "Cfedab"},     true},
        {{"abcdef",  "cfedac"},     false},
        {{"aAaAbBb",  "AABaabb"},   true},
        {{"aAaAbBb",  "AABaabB"},   false},
        {{"aAaAbBb",  "AAbaaBb"},   true},
    };
        
    return TestRunner::RunTestCases<StringPermutationInputData, bool, kNumTestCases>(testCases, &CheckPermutation);
}

