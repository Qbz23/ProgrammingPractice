// 1.5 One Away - pg91

// edit via Insert, remove, or replace 
// check if a is one or zero edits away from b 

#include "../../Shared/Testing/TestRunner.h"
#include "../Tests.h"
#include <string>
#include <math.h>

// Ok so you get away with it in 1-1 because it can be completely inline and is only consumed by main 
// However, im guessing because this defines its own type, this type exists in its own obj 
// So the testrunner youre including from this defines symbols that are consumed by this obj 
// And then theyre already defined when it goes to compile main obj. Gotta be less lazy with 
// headers and such. Maybe just a shared testcase header 

namespace Cci_1_5
{
    struct TestParam
    {
        std::string a;
        std::string b;
    };

    DEF_TESTDATA(OneAwayData, TestParam, bool);

    bool OneAwayInsertRemove(std::string shorter, std::string longer)
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

    bool OneAwayReplace(std::string a, std::string b)
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

    bool OneAway(TestParam& p)
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
};

int Tests::Run_1_5()
{
    const unsigned int kNumTestCases = 10;
    Cci_1_5::OneAwayData testCases[kNumTestCases] = { 
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
    
    return TestRunner::RunTestCases<Cci_1_5::TestParam, bool, kNumTestCases>(testCases, &Cci_1_5::OneAway);
}
