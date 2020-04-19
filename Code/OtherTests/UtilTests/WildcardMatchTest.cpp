#include "../../Shared/Testing/TestRunner.h"
#include "../OtherTests.h"
#include "../../Shared/Util/StringUtil.h"

struct WildcardMatchInput
{
    std::string wildcardStr;
    std::string otherStr;
};

DEF_TESTDATA(WildcardMatchTestData, WildcardMatchInput, bool)

static bool RunWildcardMatch(WildcardMatchInput& wmi)
{
    return Util::String::WildcardMatch(wmi.wildcardStr, wmi.otherStr);
}

int OtherTests::WildcardMatch()
{
    const unsigned int kNumTestCases = 26;
    WildcardMatchTestData testCases[kNumTestCases] = {
        // easy pass 
        {{"app*e", "apple"},                true},  // 0
        {{"*pple", "apple"},                true},  // 1
        {{"appl*", "apple"},                true},  // 2
        // easy fail 
        {{"appe", "apple"},                 false}, // 3
        {{"pple", "apple"},                 false}, // 4
        {{"appl", "apple"},                 false}, // 5
        // pass with no wildcard 
        {{"apple", "apple"},                true},  // 6
        // fail with wildcard
        {{"a*ppe", "apple"},                false}, // 7 
        {{"p*ple", "apple"},                false}, // 8
        {{"a*ppl", "apple"},                false}, // 9 
        // multiple wildcard and stress
        {{"f*bar*z", "foobarbaz"},          true},  // 10
        {{"f*bar*ay", "foobarbaz"},         false}, // 11
        {{"f*o*a*b*z", "foobarbaz"},        true},  // 12
        {{"f*o*b*b*z", "foobarbaz"},        false}, // 13
        {{"**o***b**", "foobarbaz"},        true},  // 14
        {{"**oo***b**", "foobarbaz"},       true},  // 15
        {{"*oo*b*", "foobarbaz"},           true},  // 16
        {{"*ar*", "foobarbaz"},             true},  // 17
        {{"*a*z", "foobarbaz"},             true},  // 18
        {{"f*r*", "foobarbaz"},             true},  // 19
        {{"fo*ba*ba", "foobarbaz"},         false}, // 20
        {{"fo*ba*ba*", "foobarbaz"},        false}, // 21 
        // exceptional cases 
        {{"", "foo"},                       false}, // 22
        {{"a", ""},                         false}, // 23
        {{"*", "foo"},                      true},  // 24
        {{"foo", "f*"},                     false}  // 25
    };

    return TestRunner::RunTestCases<WildcardMatchInput, bool, kNumTestCases>(testCases, &RunWildcardMatch);
};
