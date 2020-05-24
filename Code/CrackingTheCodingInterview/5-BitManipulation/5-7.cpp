// 5.7 Pairwise swap p116
//
// Swap even and odd bits with as few operations as possible 
// 0 <-> 1, 2 <-> 3, etc
// 0b101 -> 0b010
//

#include "../../Shared/Testing/TestRunner.h"
#include "../CrackingTheCodingInterview.h"
#include <vector> 
#include <algorithm>
#include <cassert>
DEF_TESTDATA(PairwiseSwapData, uint32_t, uint32_t );

// This almost exactly the same as the book solution    
// The only difference is this uses temps to make it more readable 
// and book uses a LSR b/c its working with ints 
uint32_t PairwiseSwap(uint32_t& in)
{
    // even mask is 0101 repeating, which is 5 in hex
    const uint32_t evenBitMask = 0x55555555;
    // odd mask is 1010 repeating, which is 10 in hex
    const uint32_t oddBitMask =  0xAAAAAAAA;

    const uint32_t evenBits = in & evenBitMask;
    const uint32_t oddBits = in & oddBitMask;

    return (evenBits << 1) | (oddBits >> 1);
}

int Cci::Run_5_7()
{
    const unsigned int kNumTestCases = 7;
    PairwiseSwapData testCases[kNumTestCases] = {
        {0b1,                   0b10},
        {0b10,                  0b01},    
        {0b1111,                0b1111},
        {0b1000,                0b0100},
        {0b0,                   0b0},
        {0b110010101010001,     0b1001101010100010},
        {0b110010101011111,     0b1001101010101111}
    };

    return TestRunner::RunTestCases<uint32_t, uint32_t, kNumTestCases>(testCases, &PairwiseSwap);
}

