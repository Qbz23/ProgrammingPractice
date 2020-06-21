// 8.3 - Magic Number
//
// Given a sorted array of distinct ints find a magic index if one exists 
// A magic index means A[i] = i
//

#include "../../Shared/Testing/TestRunner.h"
#include "../CrackingTheCodingInterview.h"
#include <cassert>

DEF_TESTDATA(MagicIndexData, std::vector<int>, uint32_t);

//
// Because the array is sorted you can effectively binary search for a magic index 
//
// Say input array is:
//      -2, -1, 0, 3, 5, 7, 8, 9, 10
// 
// Length is 9, guess the middle at 4 
//      A[4] = 5
// B/c array is sorted, values beyond this must be greater than 5
// Also, each subsequent slot must be greater than the previous 
// It's therefore impossible for any greater value to be a magic index 
// There is no space in a sorted distinct array for the index to 'catch up' 
//
// Go down next 'bst node' to the left 
// Sub array is [0, 3], (3 - 0) / 2 = 1 
//      A[1] = -1 
// Here, index is greater than value. We now have the same certainty to the left 
// Values can never be a magic index while also being below this value 
//
// Go down next 'bst node' to the right 
// Sub array has bounds [2, 3] middle at (3 - 2) / 2 + 2 = 2 
//      A[2] = 0 
// 
// Index still greater, go right again 
// Sub array has bounds [3, 3] middle at (3 - 3) / 2 + 3 = 3 
//      A[3] = 3 
//
// Magic index found. If this were a different value, we'd recognize that 
// LowerBound == upperBound and terminate here, concluding there is no magic index 
// 

static uint32_t GetMiddleIndex(uint32_t lowerBound, uint32_t upperBound)
{
    assert(upperBound >= lowerBound);
    return lowerBound + (upperBound - lowerBound) / 2u;
}

static uint32_t MagicIndexImpl(std::vector<int>& input, uint32_t lowerBound, uint32_t upperBound)
{
    uint32_t index = GetMiddleIndex(lowerBound, upperBound);
    uint32_t value = input[index];

    if(index == value)
    {
        return index;
    }
    // Go Right
    else if(index > value)
    {
        if(lowerBound == upperBound)
        {
            // No solution
            return (uint32_t)-1;
        }
        else 
        {
            uint32_t newLowerBound = index + 1;
            return MagicIndexImpl(input, newLowerBound, upperBound);
        }
    }
    // Go left
    else if(index < value)
    {
        if (lowerBound == upperBound)
        {
            // No solution
            return (uint32_t)-1;
        }
        else
        {
            uint32_t newUpperBound = index;
            return MagicIndexImpl(input, lowerBound, newUpperBound);
        }
    }
    else 
    {
        assert(false);
        return (uint32_t)-1;
    }
}

static uint32_t MagicIndex(std::vector<int>& input)
{
    return MagicIndexImpl(input, 0, (uint32_t)input.size());
}

int Cci::Run_8_3()
{
    static const uint32_t NoSolution = (uint32_t)-1;
    
    const unsigned int kNumTestCases = 13;
    MagicIndexData testCases[kNumTestCases] = {
        {{-1, 1, 3},                                1},     // Obvious solution
        {{0, 2, 3, 4, 5},                           0},     // Solution at first value 
        {{-1, 0, 1, 2, 4},                          4},     // Solution at last value 
        {{-8, 4, 0, 3, 7, 9},                       3},     // Simple but step up
        {{-8, 1, 3, 4, 5, 6},                       1},
        {{-1, 2, 3},                       NoSolution},     // Simple no solution
        {{1, 2, 4},                        NoSolution},     
        {{-1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, NoSolution},     // No solution deep left
        {{-1, 0, 1, 2, 3, 4, 5, 6, 7, 10}, NoSolution},     // No solution deep right
        {{-1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 
           9, 10, 12, 16, 18, 20, 21, 25},         12},     // Stress
        {{-2, -1, 2, 4, 5, 6, 7, 8, 9, 10,
           11, 12, 13, 16, 18, 20, 21, 25},         2},     
        {{-1, 0, 1, 2, 3, 4, 5, 6, 7, 8,
           9, 10, 13, 16, 18, 20, 21, 25}, NoSolution},     // Stress no soln
        {{-2, -1, 3, 4, 5, 6, 7, 8, 9, 10,
          11, 12, 13, 16, 18, 20, 21, 25}, NoSolution},
    };

    return TestRunner::RunTestCases<std::vector<int>, uint32_t, kNumTestCases>(testCases, &MagicIndex);
}
