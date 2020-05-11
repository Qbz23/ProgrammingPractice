// 3.1 Three in One - p 98

// Use a single array to implement three stacks 
// Solution below goes beyond requirements in that it can dynmically resize to store any number of values
// Also, it can represent any number of stacks, rather than just three 

#include "../../Shared/Testing/TestRunner.h"
#include "../CrackingTheCodingInterview.h"
#include "../../Shared/DataStructures/Stack.h"
#include <cassert>
#include "../../Shared/DataStructures/LinkedList.h"
#include <random>
#include <time.h>

// Helper class that prevents "lost" memory through fragmentation in internal array 
// Basically implements a stack as a circular array
// using a stack for purposes other than validation seemed against spirit of question
class FreeList 
{
    public:
        FreeList() : m_ReadIndex(-1), m_WriteIndex(-1) {}

        FreeList(unsigned int initialElements) : m_ReadIndex(0), m_WriteIndex(0)
        {
            initialElements = initialElements ? initialElements : 1;
            m_FreeIndices.resize(initialElements, -1);
        }

        // Consider "size" to be distance between readIndex and writeIndex 
        // Therefore, read == write is equivalent to size == 0
        bool Empty() const 
        {
            return m_ReadIndex == m_WriteIndex;
        }

        void Resize(unsigned int newSize)
        {   
            m_FreeIndices.resize(newSize, -1);
        }

        // Add an index to the free list, functions similarly to push
        void Add(unsigned int i) 
        {
            m_FreeIndices[m_WriteIndex++] = i;
            // If the index is now over the max capacity
            if(m_WriteIndex >= m_FreeIndices.size())
            {
                // Resize if full 
                if(m_ReadIndex == 0)
                {
                    Resize((unsigned int)m_FreeIndices.size() * 2u);
                }
                // Wrap around otherwise
                else 
                {
                    assert(m_FreeIndices[0] == -1);
                    m_WriteIndex = 0;
                }
            }
        }

        // Get an index from the free list, functions similarly to pop
        int GetIndex() 
        {
            assert(!Empty());
            int index = m_FreeIndices[m_ReadIndex];
            m_FreeIndices[m_ReadIndex] = -1;
            ++m_ReadIndex;
            if (m_ReadIndex >= m_FreeIndices.size())
            {
                m_ReadIndex = 0;
            }
            return index;
        }

    private:
        std::vector<int> m_FreeIndices;
        unsigned int m_ReadIndex;
        unsigned int m_WriteIndex;
};

// Stores data and the index of the thing below it
// aka, the index of the top of the stack before this was pushed 
struct ArrayStackNode
{
    ArrayStackNode(int v, int previousTop) : val(v), previousTopIndex(previousTop) {}
    int val;
    int previousTopIndex;
};

// Implements any number of stacks as an array
class ArrayNStack
{
public:
    // in general shouldn't pass vector by value but this is more convenient for test case init 
    ArrayNStack(unsigned int numStacks, std::vector<std::vector<int>> inputData)
    {
        assert(inputData.size() == numStacks);
        m_TopIndices.resize(numStacks, -1);

        // Initialize each stack with its input data
        for(unsigned int i = 0; i < numStacks; ++i)
        {
            unsigned int initialStackSize = (unsigned int)inputData[i].size();
            for(unsigned int j = 0; j < initialStackSize; ++j)
            {
                int previousTopIndex;
                if(j == 0)
                {
                    previousTopIndex = -1;
                }
                else 
                {
                    previousTopIndex = (int)m_InternalArray.size() - 1;
                }
                m_InternalArray.push_back({inputData[i][j], previousTopIndex});
            }
            m_TopIndices[i] = initialStackSize ? (int)m_InternalArray.size() - 1 : -1;
        }

        // Initialize free list
        m_FreeIndices = FreeList((unsigned int)m_InternalArray.size());
    }

    size_t GetNumStacks() const { return m_TopIndices.size(); }

    // Pop a value off of a particular stack 
    // puts the popped data's internal array index on the free list
    int Pop(int stackIndex)
    {
        int currentTopIndex = m_TopIndices[stackIndex];
        assert(currentTopIndex != -1);
        m_FreeIndices.Add(currentTopIndex);
        m_TopIndices[stackIndex] = m_InternalArray[currentTopIndex].previousTopIndex;
        return m_InternalArray[currentTopIndex].val;
    }

    // Push a value onto a particular stack 
    // Use an index off the free list if possible, if not, push to back of internal array
    void Push(int stackIndex, int val)
    {
        int currentTopIndex = m_TopIndices[stackIndex];
        int newTopIndex;
        if(m_FreeIndices.Empty())
        {
            newTopIndex = (int)m_InternalArray.size();
            m_InternalArray.emplace_back(val, currentTopIndex);
        }
        else 
        {
            newTopIndex = m_FreeIndices.GetIndex();
            m_InternalArray[newTopIndex].val = val;
            m_InternalArray[newTopIndex].previousTopIndex = currentTopIndex;
        }

        m_TopIndices[stackIndex] = newTopIndex;
    }

    int Top(int stackIndex)
    {
        return m_InternalArray[m_TopIndices[stackIndex]].val;
    }

    bool Empty(int stackIndex)
    {
        return m_TopIndices[stackIndex] == -1;
    }

    // For testing
    std::vector<Stack<int>> GetStackVector() const
    {
        ArrayNStack copy = ArrayNStack(*this);
        size_t numStacks = copy.m_TopIndices.size();
        std::vector<Stack<int>> outVec(numStacks);
        for(size_t stackIndex = 0; stackIndex < numStacks; ++stackIndex)
        {
            std::vector<int> stackDataVec;
            while(!copy.Empty((int)stackIndex))
            {
                stackDataVec.push_back(copy.Pop((int)stackIndex));
            }
            outVec[stackIndex] = Stack<int>(stackDataVec, false);
        }

        return outVec;
    }

private:
    // Implements a "free list" with a circular array 
    FreeList m_FreeIndices;
    // Index of the top of each stack
    std::vector<int> m_TopIndices;
    // Array storing the data of all stacks
    std::vector<ArrayStackNode> m_InternalArray;
};

DEF_TESTDATA(ArrayStackData, ArrayNStack, std::vector<Stack<int>>);

// Push and pop tons of random numbers, ending with the original stack 
// but doing your best to expose any problems in push/pop
// Use stacks to ensure popped values are as expected
static bool StressShuffle(ArrayNStack& shuffleStack, size_t numStacks)
{
    srand((unsigned int)time(0)); // seed randomness
    const unsigned int numCycles = 3; // Number of times to push/pop
    const unsigned int numPushes = 16385; // Number of pushes in each cycles
    unsigned int pushCounter = 0; // Keeps track of how many things have been pushed/popped
    for(unsigned int n = 0; n < numCycles; ++n)
    {
        // Keep track of the pushed values so they can be validated on pop
        std::vector<Stack<int>> pushedValues(numStacks);
        // Push a random value to a random stack
        while (pushCounter != numPushes)
        {
            int stackIndex = rand() % numStacks;
            int val = rand();
            shuffleStack.Push(stackIndex, val);
            pushedValues[stackIndex].Push(val);
            ++pushCounter;
        }

        // While still haven't popped everything that was pushed
        while(pushCounter != 0)
        {
            // Pop from a random stack if that stack isn't empty
            int stackIndex = rand() % numStacks;
            if(!pushedValues[stackIndex].Empty())
            {
                // Ensure popped value is as expected
                int expected = pushedValues[stackIndex].Pop();
                int actual = shuffleStack.Pop(stackIndex);
                if (expected != actual)
                {
                    // Indicate failure if expected doesnt match actual
                    return false;
                }
                --pushCounter;
            }
        }
    } 

    // All pushed/popped values were as expected, indicate success
    return true;
}

static std::vector<Stack<int>>TestStack(ArrayNStack& inputStack)
{
    if(StressShuffle(inputStack, inputStack.GetNumStacks()))
    {
        return inputStack.GetStackVector();
    }
    else 
    {
        // If it returns false, return empty vec to indicate failure
        return std::vector<Stack<int>>();
    }
}

int Cci::Run_3_1()
{
    const unsigned int kNumTestCases = 5;
    ArrayStackData testCases[kNumTestCases] = {
        {
            {1, // Num Stacks
                {
                    {1, 2, 3} // Input Stack Data 
                }
            }, 
            {
                {
                    {1, 2, 3} // Expected output stack vector
                }
            }
        },
        {
            {3, // Num Stacks
                {
                    {1, 2, 3}, // Input Stack Data
                    {4, 5, 6},
                    {7, 8, 9}
                }
            },
            {
                {
                    {{1, 2, 3}}, // Expected output stack vector
                    {{4, 5, 6}},
                    {{7, 8, 9}}
                }
            }
        },
        {
            {3,
                {
                    {1, 2, 3},
                    {},
                    {4, 5}
                }
            },
            {
                {
                    {{1, 2, 3}},
                    {{}},
                    {{4, 5}}
                }
            }
        },
        {
            {3,
                {
                    {},
                    {},
                    {}
                }
            },
            {
                {
                    {{}},
                    {{}},
                    {{}}
                }
            }
        },
        {
            {6,
                {
                    {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15},
                    {16},
                    {},
                    {17, 18, 19},
                    {20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30},
                    {31, 32}
                }
            },
            {
                {
                    {{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15}},
                    {{16}},
                    {{}},
                    {{17, 18, 19}},
                    {{20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30}},
                    {{31, 32}}
                }
            }
        }
    };

    return TestRunner::RunTestCases<ArrayNStack, std::vector<Stack<int>>, kNumTestCases>(testCases, &TestStack);
}


