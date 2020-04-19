// 1.5 One Away - pg91

// edit via Insert, remove, or replace 
// check if a is one or zero edits away from b 

#include "../../Shared/Testing/TestRunner.h"
#include "../CrackingTheCodingInterview.h"
#include <string>
#include <math.h>

struct OneAwayTestParam
{
    std::string a;
    std::string b;
};

DEF_TESTDATA(OneAwayData, OneAwayTestParam, bool);

static bool OneAwayInsertRemove(std::string shorter, std::string longer)
{
    bool alreadyChanged = false;
    for(int i = 0, j = 0; i < shorter.length(); ++i, ++j)
    {
        if(shorter[i] != longer[j])
        {
            if(alreadyChanged)
            {
                return false;
            }
            else
            {
                alreadyChanged = true;
                j += 1;
            }
        }
    }
    
    return true;
}

static bool OneAwayReplace(std::string a, std::string b)
{
    bool alreadyChanged = false;
    for(int i = 0; i < a.length(); ++i)
    {
        if(a[i] != b[i])
        {
            if(alreadyChanged)
            {
                return false;
            }
            else
            {
                alreadyChanged = true;
            }
        }
    }
    
    return true;
}

static bool OneAway(OneAwayTestParam& p)
{
    int lengthDelta = (int)(p.a.length() - p.b.length());
    //Checking for remove or insert 
    if(std::abs(lengthDelta) == 1)
    {
        bool aLonger = lengthDelta > 0;
        if(aLonger)
        {
            return OneAwayInsertRemove(p.b, p.a);
        }
        else
        {
            return OneAwayInsertRemove(p.a, p.b);
        }
    }
    //Checking for repalce
    else if(lengthDelta == 0)
    {
        return OneAwayReplace(p.a, p.b);
    }
    //if more than 1 dif in length, always false
    else 
    {
        return false;
    }
}

int Cci::Run_1_5()
{
    const unsigned int kNumTestCases = 10;
    OneAwayData testCases[kNumTestCases] = { 
        {{"pale",   "ple"},     true},
        {{"pales",  "pale"},    true},
        {{"pale",   "bale"},    true},
        {{"pale",   "bake"},    false},
        {{"abcd",   "abc"},     true},
        {{"cba",    "abcd"},    false},
        {{"",       "a"},       true},
        {{"123",    "12"},      true},
        {{"123",    "1"},       false},
        {{"abel",   "bel"},     true}};
    
    return TestRunner::RunTestCases<OneAwayTestParam, bool, kNumTestCases>(testCases, &OneAway);
}
