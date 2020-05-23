// 5.4 Next Number p116
//
// Given a positive int, print the next smallest and next largest number 
// that have the same amount of set bits 
//
// 0b0100 - 4     next smallest 0b0010 - 2     next largest 0b1000 - 8
// 0b1010 - 10    next smallest 0b1001 - 9     next largest 0b1100 - 12
//
// So for the simple case where there's space, you kist shift the smallest bit 
// left for next largest, right for next smallest. Easy path if the least 
// significant bit is surrounded by zeroes, some slightly harder examples
//
// 0b001001 - 9     next smallest 0b000110 - 6     next largest 0b001010 - 10 
// 0b011011 - 27    next smallest 0b010111 - 23    next largest 0b011101 - 29
// 0b100111 - 39    next smallest 0b011110 - 30    next largest 0b101011 - 46
//
// On the other hand, the edge case for larger is where the largest bit is shifted 
//
// 0b00111110 - 62    next smallest 0b00111101 - 61     next largest 0b001001111 - 79
// 0b11111000 - 248   next smallest 0b11110100 - 244    next largest 0b100001111 - 271
//

#include "../../Shared/Testing/TestRunner.h"
#include "../CrackingTheCodingInterview.h"
#include <vector> 
#include <algorithm>
#include <cassert>

struct NextNumberResult 
{
    NextNumberResult(uint32_t small, uint32_t large) : 
        nextSmallest(small), nextLargest(large) {}
    uint32_t nextSmallest;
    uint32_t nextLargest;
    bool operator!=(const NextNumberResult& rhs) const
    {
        return nextSmallest != rhs.nextSmallest || nextLargest != rhs.nextLargest;
    }
};

std::ostream& operator<<(std::ostream& os, const NextNumberResult& rhs)
{
    return os << "(" << rhs.nextSmallest << ", " << rhs.nextLargest << ")";
}


DEF_TESTDATA(FlipBitToWinData, uint32_t, NextNumberResult);

static uint32_t GetNextLargest(uint32_t in)
{
    uint32_t remaining = in;
    uint32_t counter = 0;
    uint32_t bitsSet = 0;

    // Find the first bit that can be shifted left into a zero 
    // If most significant bit is being shifted, ensure remaining 
    // 'bit budget' represents the smallest possible value
    while(remaining != 0)
    {
        bool bitIsSet = (remaining & 1) != 0;
        bool nextBitIsSet = (remaining & 2) != 0;
        
        // Bit is set and next isn't
        if(bitIsSet & !nextBitIsSet)
        {
            uint32_t counterBit = (1 << (counter + 1));
            // Largest bit is being shifted
            if(remaining == 1)
            {
                // Get smallest possible number for remaining bits 
                uint32_t bottomBits = (1 << bitsSet) - 1;
                return counterBit | bottomBits;
            }
            else 
            {
                // Get 1's for all bits other than the two changing 
                uint32_t counterMask = counterBit | (counterBit >> 1);

                // Invert to get all bits but those 
                uint32_t val = in & ~counterMask;

                // Add the shifted bit
                val |= counterBit;
                return val;
            }
        }

        bitsSet += bitIsSet;
        counter += 1;
        remaining >>= 1;
    }

    return -1;
}

static uint32_t GetNextSmallest(const uint32_t in)
{
    bool prevBitWasSet = true;
    uint32_t remaining = in;
    uint32_t counter = 0;
    uint32_t bitsSet = 0;

    // Find the first bit that can be shifted right into a zero 
    // ensure remaining 'bit budget' to the right of the shift 
    // represnts the largest possible value
    while(remaining != 0)
    {
        bool bitIsSet = (remaining & 1) != 0;
        // Found a 1 and there's space to shift it right 
        if(bitIsSet && !prevBitWasSet)
        {
            // Get 1's for bits already checked 
            uint32_t counterMask = (1 << (counter + 1)) - 1; 
            // Invert to retain top bits 
            uint32_t topBits = in & ~counterMask;

            // Shift the pivot bit to the right
            uint32_t shiftedBits = 1 << (counter - 1);

            // For bits below the pivot, get the largest 
            // possible value that can be represented in the 
            // remaining amount of bits
            assert(bitsSet < counter);
            uint32_t bitsSetMask = (1 << bitsSet) - 1;
            uint32_t bottomBits =  bitsSetMask << (counter - bitsSet - 1); 
            
            // combine the individual values
            return topBits | shiftedBits | bottomBits;
        }
        
        prevBitWasSet = bitIsSet;
        bitsSet += bitIsSet;
        remaining >>= 1;
        counter += 1;
    }

    return -1;
}

NextNumberResult NextNumber(uint32_t& in)
{
   return NextNumberResult(GetNextSmallest(in), GetNextLargest(in));
}

int Cci::Run_5_4()
{
    const unsigned int kNumTestCases = 8;
    // Doesn't support scenarios where there is no solution
  
    FlipBitToWinData testCases[kNumTestCases] = {
        {0b0100,        {0b0010,        0b1000}},
        {0b1010,        {0b1001,        0b1100}},
        {0b001001,      {0b000110,      0b001010}},
        {0b011011,      {0b010111,      0b011101}},
        {0b100111,      {0b011110,      0b101011}},
        {0b110110,      {0b110101,      0b111010}},
        {0b111110,      {0b111101,      0b1001111}},
        {0b11111000,    {0b11110100,    0b100001111}}
    };

    return TestRunner::RunTestCases<uint32_t, NextNumberResult, kNumTestCases>(testCases, &NextNumber);
}

