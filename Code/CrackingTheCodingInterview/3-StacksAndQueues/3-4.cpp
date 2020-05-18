// 3.4 Queue via Stacks - p99

//
// Implement a Queue class that implements a queue with two stacks
//

#include "../../Shared/Testing/TestRunner.h"
#include "../CrackingTheCodingInterview.h"
#include "../../Shared/DataStructures/Stack.h"
#include <cassert>
#include <random>
#include <time.h>
#include <queue>

//
// After initial pushes, main stack has nodes from top -> bottom as newest -> oldest
//      Main : D C B A 
// To get oldest thing out for pop, push everything else onto a separate stack 
//      Main : A       return A 
//      Extra: B C D
// That extra stack has nodes oldest -> newest, if another pop, can just return top of extra stack
//      Main : empty 
//      Extra: B C D   return B
// If want to push again however, need to push back onto main stack from extra, reversing order of nodes
//      Main : empty 
//      Extra: C D 
//      -
//      push E
//      -
//      Main : E D C
//      Extra: empty
// Main stack again has newest -> oldest
// Push returns to being simple, but pop requires a copy onto the extra stack again 
// Can think of this as having two states 
//      Push State
//          Initial State 
//          Push is cheap, just push onto main stack 
//          Pop is expensive, need to copy onto extra stack 
//          Calling pop switches to pop state 
//      Pop State 
//          Pop is cheap, just pop off of extra stack 
//          Push is expensive, need to copy back onto main stack 
//          Calling 
//

class QueueViaStacks
{
    public:
        QueueViaStacks(std::vector<int> data) : m_bOnMainStack(true)
        {
            for(auto it = data.begin(); it != data.end(); ++it)
            {
                m_MainStack.Push(*it);
            }
        }

        void Push(int val)
        {
            // On main stack, which has top -> bot as newest -> oldest; just push new item on top of stack
            if(m_bOnMainStack)
            {
                m_MainStack.Push(val);
            }
            // On extra stack, which has top -> bot as oldest -> newest 
            else 
            {
                // Push all nodes from extra stack back onto main stack
                while(!m_ExtraStack.Empty())
                {
                    m_MainStack.Push(m_ExtraStack.Pop());
                }
                // Push new item onto main stack and switch to main stack
                m_MainStack.Push(val);
                m_bOnMainStack = true;
            }
        }

        int Pop()
        {
            // On main stack, which has top -> bot as newest -> oldest
            if(m_bOnMainStack)
            {
                // Pop all but the final item onto the extra stack
                while(m_MainStack.Size() > 1)
                {
                    m_ExtraStack.Push(m_MainStack.Pop());
                }
                // Switch to extra stack
                m_bOnMainStack = false;
                // Return the final item, which is the oldest item, as desired for queue pop
                return m_MainStack.Pop();
            }
            // On extra stack, which has top -> bot as newest -> oldest; just pop oldest item off top of stack
            else 
            {
                return m_ExtraStack.Pop();
            }
        }

        bool Empty() const { return m_bOnMainStack ? m_MainStack.Empty() : m_ExtraStack.Empty(); }
        size_t Size() const { return m_bOnMainStack ? m_MainStack.Size() : m_ExtraStack.Size(); }

        // for testing
        std::vector<int> GetData() const
        {
            QueueViaStacks copy = QueueViaStacks(*this);
            std::vector<int> output;
            while(!copy.Empty())
            {
                output.push_back(copy.Pop());
            }
            return output;
        }

    private:
        Stack<int> m_MainStack;
        Stack<int> m_ExtraStack;
        bool m_bOnMainStack;
};

DEF_TESTDATA(QueueViaStacksData, QueueViaStacks, std::vector<int>);

static bool ActualMatchesExpected(int actual, int expected, int counter)
{
    if (expected != actual)
    {
        std::string debugString = "Stress Shuffle Failed! Actual: " + std::to_string(actual) +
            " doesn't match expected " + std::to_string(expected) + " at counter " + std::to_string(counter) + "\n";
        Log::Debug(debugString);
        return false;
    }
    else 
    {
        return true;
    }
}

// Push and pop tons of random numbers, ending with the original stack 
// but doing your best to expose any problems in push/pop
// Use queues to ensure popped values are as expected
static bool StressShuffle(QueueViaStacks& shuffleQueue)
{
    srand((unsigned int)time(0)); // seed randomness
    const unsigned int numCycles = 3; // Number of times to push/pop
    const unsigned int numActions = 2049; // Number of pushes in each cycles
    unsigned int pushCounter; // Keeps track of how many things have been pushed/popped
    unsigned int popCounter;

    for(unsigned int n = 0; n < numCycles; ++n)
    {
        pushCounter = 0;
        popCounter = 0;
        // Copy initial values into expected pushed values, as those values will 
        // be popped off the queue and checked later 
        std::queue<int> pushedValues;
        std::vector<int> initialData = shuffleQueue.GetData();
        for (unsigned int i = 0; i < initialData.size(); ++i)
        {
            pushedValues.push(initialData[i]);
            pushCounter++;
        }
        
        // Push and pop until pushes hit limit
        while (pushCounter <= numActions)
        {
            // If nothing to pop, just push 
            // If something to pop, 50/50 chance to push or pop 
            bool shouldPop = popCounter < pushCounter && (rand() % 2);
            if (shouldPop)
            {
                // Ensure popped value is as expected
                int expected = pushedValues.front();
                pushedValues.pop();
                int actual = shuffleQueue.Pop();
                if (!ActualMatchesExpected(actual, expected, popCounter))
                {
                    return false;
                }
                ++popCounter;
            }
            else 
            {
                int val = rand();
                shuffleQueue.Push(val);
                pushedValues.push(val);
                ++pushCounter;
            }          
        }

        // Pop off anything extra left 
        while(popCounter != numActions)
        {
            // Ensure popped value is as expected
            int expected = pushedValues.front();
            pushedValues.pop();
            int actual = shuffleQueue.Pop();
            if (!ActualMatchesExpected(actual, expected, popCounter))
            {
                return false;
            }
            ++popCounter;
        }

        // Restore initial state
        shuffleQueue = QueueViaStacks(initialData);
    } 

    // All pushed/popped values were as expected, indicate success
    return true;
}

static std::vector<int>TestStack(QueueViaStacks& inputQueue)
{
    if(StressShuffle(inputQueue))
    {
        return inputQueue.GetData();
    }
    else 
    {
        // If it returns false, return empty vec to indicate failure
        return std::vector<int>();
    }
}

int Cci::Run_3_4()
{
    const unsigned int kNumTestCases = 3;
    QueueViaStacksData testCases[kNumTestCases] = {
    //      input                      expected
        {{{1, 2, 3}},                   {1, 2, 3}}, // Honestly stress shuffle is the real test
        {{{}},                          {}}, 
        {{{1, 2, 3, 4, 5, 6, 7, 8, 9}}, {1, 2, 3, 4, 5, 6, 7, 8, 9}}
    };

    return TestRunner::RunTestCases<QueueViaStacks, std::vector<int>, kNumTestCases>(testCases, &TestStack);
}

