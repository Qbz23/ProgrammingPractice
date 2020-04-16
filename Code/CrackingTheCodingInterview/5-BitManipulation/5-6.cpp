// 5-6 Conversion - pg 116
// Write a function to determine the number of bits that must be flipped to convert int a to b 

#include "../Tests.h"
#include "../../Shared/Testing/TestRunner.h"

struct ConversionTestParam
{
    int a;
    int b;
};

DEF_TESTDATA(ConversionData, ConversionTestParam, int);

//Could be better, probably better to find next highest power of 2 and start from that num of bits
int Conversion(ConversionTestParam& p)
{
    int numBits = 4 * sizeof(p.a);
    int checkBits = p.a ^ p.b;
    int numFlips = 0;
    for(int i = 0; i < numBits; ++i)
    {
        int bit = 1 << i;
        if((bit & checkBits) != 0)
        {
            numFlips += 1;
        }
    }
    
    return numFlips;
}

int Tests::Run_5_6()
{
    const unsigned int kNumTestCases = 8; 
    ConversionData testCases[kNumTestCases] = {
        {{1,    2},     2},     //01        10
        {{1,    3},     1},     //1         11
        {{2,    4},     2},     //010       100
        {{10,   2},     1},     //1010      0010
        {{63,   0},     6},     //111111    000000
        {{65,   13},    3},     //1000001   0001101
        {{27,   27},    0},
        {{3,    31},    3},     //00011     11111
    };
    
    return TestRunner::RunTestCases<ConversionTestParam, int, kNumTestCases>(testCases, &Conversion);
}