// 5.3 Flip Bit to Win - p11
//
// Given an input number, determine the length of the longest sequence 
// of consecutive 1's that could be created by flipping a single bit
//
// 1775         - 0b11011101111 
// Fllip 5th    - 0b11011111111
// 8 consecutive 1's 
//

#include "../../Shared/Testing/TestRunner.h"
#include "../CrackingTheCodingInterview.h"
#include <vector> 
#include <algorithm>
#include <cassert>
DEF_TESTDATA(FlipBitToWinData, uint32_t, uint32_t );

//
// Somehwat similar to book soln. Book instead stores the length all sequences, 0's and 1's, 
// And you can determine if two 1's sequences can merge by checking the length of the 0 sequence between
// Book's advanced solution determines the result in-place, without requiring a second pass. 
// It basically "always" merges, but sets previous length to 0 if the merge would be invalid 
// Also better in that it LSR's the input down to 0 rather than checking all N bits. 
//
unsigned int FlipBitToWin(uint32_t& in)
{
    // Basically want to "Tokenize" on 0, just need lengths of tokens though 
    const uint32_t bitWidth = 32;
    // All bits already set.
    if(in == ~0)
    {
        return bitWidth;
    }

    // Used to store info about sequences of 1's 
    struct BitSequence
    {
        BitSequence(uint32_t _start, uint32_t _end) :  
            start(_start), end(_end), length(end - start)
        {
            assert(end > start);
        }

        const uint32_t start;
        const uint32_t end;
        const uint32_t length; // could calc every time but might as well store result
    };

    // Do a pass over the string, detecting each sequence of 1's 
    std::vector<BitSequence> sequences;
    bool inSequence = false;
    uint32_t sequenceStart = 0;
    uint32_t lastSequenceEnd = 0;
    for(uint32_t i = 0; i < bitWidth; ++i)
    {
        bool bitSet = ((1 << i) & in);
        if(inSequence)
        {
            // If already in a sequence, check if this is the end,
            // either by hitting a 0 
            if(!bitSet)
            {
                sequences.emplace_back(sequenceStart, i);
                inSequence = false;
            }
            // or end of input
            else if(i == bitWidth - 1)
            {
                // the end is the index of the 0 after the sequence
                // add 1 to mimic this for tokens ended by end of number
                sequences.emplace_back(sequenceStart, i + 1);
                inSequence = false;
            }
        }
        else 
        {
            //  If not in a sequence, check if this is the start of a new one
            if(bitSet)
            {
                sequenceStart = i;
                inSequence = true;
                if(i == bitWidth - 1)
                {
                    sequences.emplace_back(sequenceStart, sequenceStart + 1);
                }
            }
        }
    }

    // Check how sequences of 1's might be combined or lengthened to determine 
    // what the length of the longest possible sequence is
    uint32_t numSequences = (uint32_t)sequences.size();
    uint32_t maxLength = 0;
    if(numSequences > 0)
    {
        for (uint32_t i = 0; i < numSequences; ++i)
        {
            if (i < numSequences - 1)
            {
                bool hasAdjacentSequence = (sequences[i + 1].start - sequences[i].end) == 1;
                if(hasAdjacentSequence)
                {
                    // Larger sequence equal to sum of both plus the additional 1 bridging them 
                    maxLength = std::max(sequences[i].length + sequences[i + 1].length + 1, maxLength);
                }
                else 
                {
                    // if not the last token, you can stick a 1 on the end at least
                    maxLength = std::max(sequences[i].length + 1, maxLength);
                }
            }
            else 
            {
                // There is no token following this
                // Can always add a single 1 to the sequence
                maxLength = std::max(sequences[i].length + 1, maxLength);
            }
        }
    }
    else 
    {
        assert(in == 0);
        maxLength = 1;
    }

    return maxLength;
}

int Cci::Run_5_3()
{
    const unsigned int kNumTestCases = 8;
    FlipBitToWinData testCases[kNumTestCases] = {
        {0b11011101111,      8},    // book 
        {0b11001101,         4},    // dont join sequence two apart
        {0b11010011110,      5},    // add 1 to final
        {0b1101001111,       5},    // 
        {0b11100000101,      4},    // add 1 to first 
        {0,                  1},    // all 0
        {~0u,               32},    // all 1
        {~1u,               32}     // all 1 but 1 
    };

    return TestRunner::RunTestCases<uint32_t, uint32_t, kNumTestCases>(testCases, &FlipBitToWin);
}

