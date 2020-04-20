// 1.9 String Rotation - p91
//
// Given a method IsSubstring and two strings, check if s2 is a rotation of s1
// using only one call to IsSubstring
// waterbottle is a rotation of erbottlewat
//

#include "../../Shared/Testing/TestRunner.h"
#include <string>
#include "../CrackingTheCodingInterview.h"

struct IsRotationInputData
{
    std::string s1;
    std::string s2;
};

DEF_TESTDATA(IsRotationData, IsRotationInputData, bool);

// Check if s2 is a subtring of s1
static bool IsSubstring(std::string str, std::string checkSubstr)
{
    return str.find(checkSubstr) != -1;
}

bool IsRotation(IsRotationInputData& id)
{
    // Can't be a rotation if not the same size and not zero
    if(id.s1.size() != id.s2.size() || id.s1.empty())
    {
        return false;
    }
    else 
    {
        // s1 = erbottlewat, s2 = waterbottle
        // Is there a point where these can be split 
        // such that s1 = xY and s2 = Yx
        // If add s1 to itself, it equals xYxY
        // s1s1 then would contain Yx and therefore s2 if it's a rotation 
        return IsSubstring(id.s1 + id.s1, id.s2);
    }
}

int Cci::Run_1_9()
{
    const unsigned int kNumTestCases = 13;
    IsRotationData testCases[kNumTestCases] = 
    {
        // simple pass
        {{"erbottlewat", "waterbottle"},        true},
        {{"waterbottle", "erbottlewat"},        true},
        {{"waterbottle", "waterbottle"},        true},
        //  simple fail
        {{"erbottlewat", "waterbottls"},         false},
        {{"erbottlewat", "xaterbottle"},         false},
        // size mismatch
        {{"ab", "a"},                           false},
        {{"a", "ab"},                           false},
        // empty strs
        {{"", "a"},                             false},
        {{"a", ""},                             false},
        {{"", ""},                              false},
        // repeated tokens
        {{"foobarfoo", "barfoofoo"},            true},
        {{"foobarfoo", "foofoobar"},            true},
        {{"foobabarfoo", "foofoobarfoo"},       false}
    };

    return TestRunner::RunTestCases<IsRotationInputData, bool, kNumTestCases>(testCases, &IsRotation);
}
