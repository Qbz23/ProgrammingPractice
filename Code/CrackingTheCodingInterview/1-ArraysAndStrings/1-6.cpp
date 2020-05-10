// 1.6 String Compression - pg91

// perform basic string compression using the counts of repeated characters 
// for example: aabcccccaaa would become a2b1c5a3
// If the compressed string would be larger, return the original string 
// String only has upper and lowercase letters

#include "../../Shared/Testing/TestRunner.h"
#include "../CrackingTheCodingInterview.h"
#include <string>
#include <iostream>

DEF_TESTDATA(StringCompressionData, std::string, std::string)

// 
// The book points out some of the efficiency problems with a straightforward 
// one pass approach appending to an output string as you go. It reccomends you 
// use a string builder. The solution below basically implements that idea  
// 
static std::string StringCompress(std::string& input)
{
    size_t length = input.length();
    // Empty strings are as compressed as theyre ever gonna be 
    if(length == 0)
    {
        return input;
    }

    // Get each run of subsequent chars and its length
    std::vector<std::pair<char, size_t>> orderedCharCounts;
    char currentChar = input[0];
    size_t charCount = 1;
    for(size_t i = 1; i < length; ++i)
    {
        char checkChar = input[i];
        // If matches, continue your existing run
        if(currentChar == checkChar)
        {
            charCount += 1;
        }
        // If different, previous run over, start a new run
        else 
        {
            orderedCharCounts.push_back(std::make_pair(currentChar, charCount));
            currentChar = checkChar;
            charCount = 1;
        }
    }
    // One final run to store
    orderedCharCounts.push_back(std::make_pair(currentChar, charCount));

    // Store the information into an output string
    std::string outStr;
    // It cannot be bigger than the input string, so can initially resize it to that length
    outStr.resize(length);
    size_t addedCharacters = 0;
    for(auto it = orderedCharCounts.begin(); it != orderedCharCounts.end(); ++it)
    {
        char c = it->first;
        size_t count = it->second;
        std::string countStr = std::to_string(count);
        size_t additionSize = countStr.length() + 1;
        // If adding these new chars would lead to it being bigger than input
        if(addedCharacters + additionSize >= length)
        {
            // input is shorter, just return input
            return input;
        }
        // If there's still space left for this new compression code
        else 
        {
            // Add compression code to output string
            outStr[addedCharacters] = c;
            for(size_t i = 0; i < additionSize - 1; ++i)
            {
                outStr[addedCharacters + i + 1] = countStr[i];
            }
            addedCharacters += additionSize;
        }
    }

    // Trim extra space off the end of output string and return it
    return outStr.substr(0, addedCharacters);
}

int Cci::Run_1_6()
{
    const unsigned int kNumTestCases = 11;
    StringCompressionData testCases[kNumTestCases] = {
        {"aabcccccaaa",                 "a2b1c5a3"},
        {"abcd",                        "abcd"},
        {"aabcd",                       "aabcd"},
        {"aabbccdd",                    "aabbccdd"},
        {"aabbccddd",                   "a2b2c2d3"},
        {"aaaaaaaaaaaaaabbbbbbbbbbb",   "a14b11"},
        {"aAbBcCdDd",                   "aAbBcCdDd"},
        {"AAbbBCCDDDD",                 "A2b2B1C2D4"},
        {"",                            ""},
        {"a",                           "a"},
        {"aaa",                         "a3"}
    };
        
    return TestRunner::RunTestCases<std::string, std::string, kNumTestCases>(testCases, &StringCompress);
}

