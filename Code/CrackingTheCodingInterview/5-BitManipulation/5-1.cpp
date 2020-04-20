// 5.1 Insertion - p115 
//
// Given two 32 bit numbers, N and M, and two bit positions, i and j.
// Insert M into N such that M starts at bit J and ends at bit i
// You can assume the bits j through i have enough space.
//
// N = 10000000000, M = 10011. i = 2, j = 6. 
// Output N = 10000101100
//

#include "../../Shared/Testing/TestRunner.h"
#include "../CrackingTheCodingInterview.h"

struct InsertionTestParam 
{
    int dst; 
    int insert;
    int start; 
    // It might seem like with the given assumption, j is meaningless
    // However, j - i lets you infer relevant bit width of insert, 
    // which might be annoying otherwise
    int end;
};

DEF_TESTDATA(InsertionData, InsertionTestParam, int);

static int Insertion(InsertionTestParam& tp)
{
    for(int i = tp.start; i <= tp.end; ++i)
    {
        // Can't just or, would allow a dst 1 to override an insert 0 
        // Can't just and, would allow a dst 0 to override an insert 1
        int insertTestBit = 1 << (i - tp.start);
        int insertSetBit = 1 << i;
        // If insert is set, set dst with or
        if((insertTestBit & tp.insert) != 0)
        {
            tp.dst |= insertSetBit;
        }
        // if insert isnt set, set dst with and
        else 
        {
            tp.dst &= ~(insertSetBit);
        }
    }

    return tp.dst;
}

//
// Book soln is a little better 
//  1. Clear j through i in dst 
//  2. Shift insert so it lines up with dst location
//  3. Merge them 
// 
//  3 shifts rather than 2 * (J - I )
//  2 bitwise eq ops rather than (J - I)
//
static int InsertionMerge(InsertionTestParam& tp)
{
    // Start with all 1's, then add 0's on both sides 
    int allBitsSet = ~0;
    int left = allBitsSet << (tp.end + 1);
    int right = (1 << tp.start) - 1;
    int clearMask = left | right;

    tp.dst &= clearMask;
    tp.dst |= (tp.insert << tp.start);

    return tp.dst;
}

int Cci::Run_5_1()
{
    const unsigned int kNumTestCases = 6;
    InsertionData testCases[kNumTestCases] = {
        // book example
        {{0b10000000000,    0b10011,     2, 6}, 0b10001001100},
        // other tests
        {{0b1000,           0b10,        0, 1}, 0b1010},
        {{0b1000,           0b10,        1, 2}, 0b1100},
        {{0b1000,           0b01,        1, 2}, 0b1010},
        {{0b100,            0b0,         2, 2}, 0b0},
        {{0b10001,          0b0,         2, 4}, 0b1}
    };

    int failedCases = TestRunner::RunTestCases<InsertionTestParam, int, kNumTestCases>(testCases, &Insertion);
    failedCases += TestRunner::RunTestCases<InsertionTestParam, int, kNumTestCases>(testCases, &InsertionMerge);
    return failedCases;
}
