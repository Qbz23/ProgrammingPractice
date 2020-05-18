// 3.3 Stack of Plates - p99

//
// Iamgine real stacks of plates, they cant get too high or they'll topple 
// Implement a SetOfStacks which functions as a stack but stores its data 
// in multiple internal stacks, not exceeding a certain capacity 
//
// Not implemented here, maybe future? 
//  Follow up, implement PopAt(index) 
//      Two options, implement a system to keep track of holes in your set of stacks 
//      or implement a system to remove the bottom of a stack to shift the stack back after each 
//          ex: size = 3, top -> bot
//          1 2 3  4 5 6  7 8 9
//          PopAt(2)
//          1 2 3  4 5 6    8 9
//              Remove 6 from bottom of stack 1, push it onto stack 2 
//              Remove 3 from bottom of stack 0, push it onto stack 1 
//            1 2  3 4 5  6 8 9
//      Probably just use doubly linked list with tail ptr
//

#include "../../Shared/Testing/TestRunner.h"
#include "../CrackingTheCodingInterview.h"
#include "../../Shared/DataStructures/Stack.h"
#include <cassert>
#include <random>
#include <time.h>

class SetOfStacks
{
    public:
        SetOfStacks(unsigned int substackCapacity, std::vector<int> data) :
            m_SubstackCapacity(substackCapacity), m_Size(0)
        {
            assert(substackCapacity != 0);

            // push in reverse order so input and output can be top -> bot
            std::reverse(data.begin(), data.end());

            for(auto it = data.begin(); it != data.end(); ++it)
            {
                Push(*it);
            }
        }

        // for testing
        std::vector<Stack<int>> GetStacks() const 
        { 
            std::vector<Stack<int>> output;
            for(auto it = m_Stacks.begin(); it != m_Stacks.end(); ++it)
            {
                if(!it->Empty())
                {
                    output.push_back(*it);
                }
            }

            // the top is the back of the vector, reverse out, because tester expects top->bot 
            std::reverse(output.begin(), output.end()); 
            return output;
        }

        unsigned int GetSubstackCapacity() const { return m_SubstackCapacity; }
        bool Empty() const  { return m_Size != 0; }

        void Push(int val)
        {
            unsigned int index = GetSubstackIndex(true);
            if(index < m_Stacks.size())
            {
                m_Stacks[index].Push(val);
            }
            else 
            {
                m_Stacks.push_back(Stack<int>({val}));
            }
            
            m_Size += 1;
        }

        int Pop()
        {
            unsigned int index = GetSubstackIndex(false);
            int val = m_Stacks[index].Pop();
            m_Size -= 1;

            return val;
        }

    private:
        unsigned int GetSubstackIndex(bool push) const 
        { 
            if(push)
            {
                return m_Size / m_SubstackCapacity;
            }
            else if(m_Size > 0)
            {
                return (m_Size - 1) / m_SubstackCapacity;
            }
            else 
            {
                return 0;
            }
        }

        const unsigned int m_SubstackCapacity;
        unsigned int m_Size;
        std::vector<Stack<int>> m_Stacks;
        
};

DEF_TESTDATA(SetOfStackData, SetOfStacks, std::vector<Stack<int>>);

// Push and pop tons of random numbers, ending with the original stack 
// but doing your best to expose any problems in push/pop
// Use stacks to ensure popped values are as expected
static bool StressShuffle(SetOfStacks& shuffleStack)
{
    srand((unsigned int)time(0)); // seed randomness
    const unsigned int numCycles = 3; // Number of times to push/pop
    const unsigned int numActions = 16385; // Number of pushes in each cycles
    unsigned int pushCounter = 0; // Keeps track of how many things have been pushed/popped
    unsigned int popCounter = 0;
    for(unsigned int n = 0; n < numCycles; ++n)
    {
        // Keep track of the pushed values so they can be validated on pop
        Stack<int> pushedValues;
        
        // Push and pop until pushes hit limit
        while (pushCounter != numActions)
        {
            // If nothing to pop, just push 
            // If something to pop, 50/50 chance to push another or pop 
            bool shouldPop = popCounter < pushCounter && (rand() % 2);
            if(shouldPop)
            {
                // Ensure popped value is as expected
                int expected = pushedValues.Pop();
                int actual = shuffleStack.Pop();
                if (expected != actual)
                {
                    // Indicate failure if expected doesnt match actual
                    return false;
                }
                ++popCounter;
            }
            else 
            {
                int val = rand();
                shuffleStack.Push(val);
                pushedValues.Push(val);
                ++pushCounter;
            }          
        }

        // Pop off anything extra left 
        while(popCounter != numActions)
        {
            // Ensure popped value is as expected
            int expected = pushedValues.Pop();
            int actual = shuffleStack.Pop();
            if (expected != actual)
            {
                // Indicate failure if expected doesnt match actual
                return false;
            }
            ++popCounter;
        }
    } 

    // All pushed/popped values were as expected, indicate success
    return true;
}

static std::vector<Stack<int>>TestStack(SetOfStacks& inputStack)
{
    if(StressShuffle(inputStack))
    {
        return inputStack.GetStacks();
    }
    else 
    {
        // If it returns false, return empty vec to indicate failure
        return std::vector<Stack<int>>();
    }
}

int Cci::Run_3_3()
{
    const unsigned int kNumTestCases = 6;
    SetOfStackData testCases[kNumTestCases] = {
    // Capacity     input                      expected
        {{1,    {{1, 2, 3}}},               {{{{1}}, {{2}}, {{3}}}}},
        {{3,    {{1, 2, 3}}},               {{{1, 2, 3}}}},
        {{2,    {{1, 2, 3, 4, 5}}},         {{{{1}}, {{2, 3}}, {{4, 5}}}}},
        {{4,    {{1, 2, 3, 4, 5}}},         {{{{1}}, {{2, 3, 4, 5}}}}},
        {{2,    {{1, 2, 3, 4, 5, 6, 7}}},   {{{{1}}, {{2, 3}}, {{4, 5}}, {{6, 7}}}}},
        {{1,    {}},                        {}}
    };

    return TestRunner::RunTestCases<SetOfStacks, std::vector<Stack<int>>, kNumTestCases>(testCases, &TestStack);
}

