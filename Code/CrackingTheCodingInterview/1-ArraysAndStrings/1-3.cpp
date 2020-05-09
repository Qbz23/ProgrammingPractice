// 1.3 URLify - pg90

// Replace all strings in a string with %20. 
// Use a character array and do it in place 
// You can assume there's enough space at the end of the char array to store the %20's

#include "../../Shared/Testing/TestRunner.h"
#include "../CrackingTheCodingInterview.h"
#include <string>
#include <iostream>
#include <stack>

DEF_TESTDATA(URLifyData, std::string, std::string)

//
// Book soln is pretty similar, checks for spaces again in the second pass rather 
// than storing indices. This allows the logic to be simplified: shifting over one or 
// three characters moving backwards through the string starting from a point 
// calculated by the number of spaces. While simplier, probably slightly less 
// efficient in that the second pass is done  over each char for book solution 
// but just each space for this solution
//
static void URLifyImpl(char* pInout, unsigned int initialStrLength)
{
    // No change needed
    if(initialStrLength == 0)
    {
        return;
    }
    
    // Get space indices 
    char* pWalker = &pInout[0];
    bool bInToken = false;
    unsigned int index = 0;
    unsigned int numSpace = 0;
    std::stack<unsigned int> spaceIndices;
    for(unsigned int i = 0; i < initialStrLength; ++i)
    {
        if(pWalker[i] == ' ')
        {
            spaceIndices.push(i);
        }
    }

    // Going backwards (b/c stack) through space indices, 
    // shift the string right in-place
    unsigned int totalSpaces = (unsigned int)spaceIndices.size();
    unsigned int handledSpaces = 0;
    unsigned int previousSpaceIndex = (unsigned int)-1;
    const unsigned int spaceTokenLength = 3;
    char spaceToken[spaceTokenLength] = {'%', '2', '0'};
    while(!spaceIndices.empty())
    {
        unsigned int spaceIndex = spaceIndices.top(); 
        // Each space will requirement a shift over of 
        unsigned int precedingSpaces = totalSpaces - handledSpaces;
        unsigned int srcOffset = spaceIndex + 1;
        // Each space already took one char, so it needs TokenLen - 1 additional chars in out str
        unsigned int dstOffset = srcOffset + precedingSpaces * (spaceTokenLength - 1);
        unsigned int size;
        if(handledSpaces == 0)
        {
             size = initialStrLength - spaceIndex - 1;
        }
        else 
        {
            size = previousSpaceIndex - spaceIndex - 1;
        }
        //Log::Debug("Copying " + std::to_string(size) + " bytes with src offset " + 
        //    std::to_string(srcOffset) + " and dst offset " + std::to_string(dstOffset) + "\n");
        memcpy(pInout + dstOffset, pInout + srcOffset, size);
        memcpy(pInout + (dstOffset - 3), spaceToken, 3);
        //Log::Debug("Resulting String: " + std::string(pInout) + "\n");

        handledSpaces += 1;
        previousSpaceIndex = spaceIndex;
        spaceIndices.pop();
    }
}

static std::string URLify(std::string& input)
{
    // Preprocess the input to use strings for test infra convenience 
    // while still matching the requirements of the question 
    unsigned int numSpaces = 0;
    unsigned int inputLength = (unsigned int)input.length();
    for(unsigned int i = 0; i < inputLength; ++i)
    {
        if(input[i] == ' ')
        {
            numSpaces += 1;
        }
    }
    const unsigned int kSpaceTokenLength = 3;
    unsigned int newLength = kSpaceTokenLength * numSpaces + inputLength + 1 - numSpaces;

    char* inoutCharArray = new char[newLength];
    memcpy(inoutCharArray, input.data(), inputLength);
    memset(inoutCharArray + inputLength, (int)' ', (newLength - 1) - inputLength);
    inoutCharArray[newLength - 1] = '\0';
    
    // Run Test
    URLifyImpl(inoutCharArray, inputLength);
    std::string result(inoutCharArray);

    delete [] inoutCharArray;
    return result;
}

int Cci::Run_1_3()
{
    const unsigned int kNumTestCases = 8;
    // Book specifies no rules as to case, I'm going to treat case as different 
    URLifyData testCases[kNumTestCases] = {
        // Basic
        {"Mr John Smith",                       "Mr%20John%20Smith"},
        {" ",                                   "%20"},
        {"",                                    ""},
        // Leading Space
        {" Mr John Smith",                      "%20Mr%20John%20Smith"},
        // Trailing Space 
        {"Mr John Smith ",                      "Mr%20John%20Smith%20"},
        // Multispace
        {"Mr  John  Smith",                     "Mr%20%20John%20%20Smith"},
        // Stress
        {" %20 Mr%20  %20John %20 Smith%20 ",   "%20%20%20Mr%20%20%20%20John%20%20%20Smith%20%20"},
        {"1 2  3   4    5     ",                "1%202%20%203%20%20%204%20%20%20%205%20%20%20%20%20"}
    };
        
    return TestRunner::RunTestCases<std::string, std::string, kNumTestCases>(testCases, &URLify);
}

