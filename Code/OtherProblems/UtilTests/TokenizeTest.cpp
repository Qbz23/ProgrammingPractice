#include "../../Shared/Testing/TestRunner.h"
#include "../Tests.h"
#include "../../Shared/Util/StringUtil.h"

struct TokenizeInput
{
    std::string str;
    char delim;
};

DEF_TESTDATA(TokenizeTestData, TokenizeInput, std::vector<std::string>)

static std::vector <std::string> RunTokenize(TokenizeInput& ti)
{
    return Util::String::Tokenize(ti.str, ti.delim);
}

int Tests::Tokenize()
{
    const unsigned int kNumTestCases = 5;
    TokenizeTestData testCases[kNumTestCases] = {
        {{"xbybz", 'b'},        {"x", "y", "z"}},
        {{"a1a2a", 'a'},        {"1", "2"}},
        // All delim
        {{"aaaaa", 'a'},        {}},
        // Consecutive delim
        {{"aabaacaaa", 'a'},    {"b", "c"}},
        // no delim
        {{"foo", 'x'},          {"foo"}}
      };

    return TestRunner::RunTestCases<TokenizeInput, std::vector<std::string>, kNumTestCases>(testCases, &RunTokenize);
};
