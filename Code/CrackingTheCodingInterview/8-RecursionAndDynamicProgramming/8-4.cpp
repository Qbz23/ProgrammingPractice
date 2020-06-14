// 8.4 - Power Set
//
// Write a method to return all subsets of a set 
//

#include "../../Shared/Testing/TestRunner.h"
#include "../CrackingTheCodingInterview.h"
#include <unordered_map>

DEF_TESTDATA(PowerSetData, std::vector<int>, bool);

static std::vector<std::vector<int>> PowerSetImpl(const std::vector<int>& input, int index)
{
    std::vector<std::vector<int>> output;
    // Done, just return empty
    if(index == input.size())
    {
        std::vector<int> emptySet; 
        output.emplace_back(emptySet);
    }
    else 
    {
        // Advance startIndex to get subsets of size N-1 without val at index
        output = PowerSetImpl(input, index + 1);
        // Can't add straight to output, invalidates iterator 
        std::vector<std::vector<int>> newSubsets;
        for(auto it = output.begin(); it != output.end(); ++it)
        {
            std::vector<int> newSubset; 
            // Add relevant value to all subsets
            newSubset.insert(newSubset.begin(), it->begin(), it->end());
            newSubset.push_back(input[index]);
            newSubsets.push_back(newSubset);
        }
        output.insert(output.end(), newSubsets.begin(), newSubsets.end());
    }

    return output;
}

static bool PowerSet(std::vector<int>& input)
{
    std::vector<std::vector<int>> allSubsets = PowerSetImpl(input, 0);

    // It would be pretty annoying to have expected subsets to validate against 
    // but we can know the total amount of sets we expect and we can also expect 
    // the total counts of values across all sets to be equal. The only other potential 
    // source of error would be a value being 'dropped' and count being equally spread 
    // across other values

    // Expected Set count is 2^N where N is the size of the input set 
    // {1}          ->      2^1     = {}, {1}
    // {1, 2}       ->      2^2     = {}, {1}, {2}, {1, 2}
    // {1, 2, 3}    ->      2^3     = {}, {1}, {2}, {1, 2}, {3}, {1, 3}, {2, 3}, {1, 2, 3}
    // It makes sense that each new value doubles the subset count because each 
    // existing subset now has a new version with the added value included 
    size_t expectedSize = size_t(1u) << input.size();
    if(allSubsets.size() != expectedSize)
    {
        Log::Debug("8-4 Failed. Expected " + std::to_string(expectedSize) + ", but found " + 
                   std::to_string(allSubsets.size()) + ".\n");
        return false;
    }

    // Count up values
    std::unordered_map<int, uint32_t> counts;
    for(auto it = allSubsets.begin(); it != allSubsets.end(); ++it)
    {
        // Also check for uniqueness here, repeated values could generate wrong output 
        // that could sneak past the other detection here
        std::unordered_map<int, bool> foundVals;
        for(auto valIt = it->begin(); valIt != it->end(); ++valIt)
        {
            auto countIt = counts.find(*valIt);
            if(countIt == counts.end())
            {
                counts.insert(std::make_pair(*valIt, 1u));
            }
            else 
            {
                countIt->second += 1;
            }

            // Ensure this value wasn't already found in this set 
            auto foundIt = foundVals.find(*valIt);
            if(foundIt == foundVals.end())
            {
                foundVals.insert(std::make_pair(*valIt, true));
            }
            else 
            {
                Log::Debug("8-4 Failed. When counting values, found repeated value in set: " 
                    + std::to_string(*valIt) + ".\n");
                return false;
            }
        }
    }
    // Ensure counts are equal
    uint32_t expectedCount = 0;
    for(auto it = counts.begin(); it != counts.end(); ++it)
    {
        if(expectedCount == 0)
        {
            expectedCount = it->second;
        }
        else if(expectedCount != it->second) 
        {
            Log::Debug("8-4 Failed. For value " + std::to_string(it->first) + ", expected count " + 
                std::to_string(expectedCount) + " but found " + std::to_string(it->second) + ".\n");
            return false;
        }
    }

    // Ensure values weren't lost or changed somehow
    for(auto it = input.begin(); it != input.end(); ++it)
    {
        if (counts.find(*it) == counts.end())
        {
            Log::Debug("8-4 Failed. Failed tp find input value " + std::to_string(*it) + " in output sets.\n");
            return false;
        }
    }
    
    return true;
}

int Cci::Run_8_4()
{
    const unsigned int kNumTestCases = 5;
    PowerSetData testCases[kNumTestCases] = {
        {{1 },                      true},
        {{0, 2},                    true},
        {{-2, 4, 12},               true},
        {{67, 109, 33, -45, 4},     true},
        {{11, 42, 67, 19, -32},     true}
    };

    return TestRunner::RunTestCases<std::vector<int>, bool, kNumTestCases>(testCases, &PowerSet);
   
}
