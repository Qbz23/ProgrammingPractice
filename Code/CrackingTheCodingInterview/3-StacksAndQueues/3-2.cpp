// 3.2 Stack Min - p 98

// Design a stack that implements min 
// push, pop, and min must be O(1)

#include "../../Shared/Testing/TestRunner.h"
#include "../CrackingTheCodingInterview.h"
#include "../../Shared/DataStructures/Stack.h"

struct MinNode
{
    MinNode(int v) : val(v), minBelow(INT_MAX) {}
    // Stack<T> implements == to make testing easier. This isn't actually used though
    bool operator==(const MinNode& rhs) { return val == rhs.val && minBelow == rhs.minBelow; }
    int val;
    int minBelow;
};

class StackMin : public Stack<MinNode>
{
    public:
        StackMin(std::vector<int> d) : mCurrentMin(INT_MAX)
        {
            std::reverse(d.begin(), d.end());
            for (auto it = d.begin(); it != d.end(); ++it)
            {
                Push(MinNode(*it));
            }
        }

        int Min() const 
        {
            return mCurrentMin;
        }

        // Update the min if the new node's value is below the current min
        inline void Push(MinNode newNode) override
        {
            newNode.minBelow = mCurrentMin;
            mStack.push(newNode);
            mCurrentMin = std::min(newNode.val, mCurrentMin);
        }
         
        // Update the min to the min for the nodes below, stored on the popped node
        inline MinNode Pop() override
        {
            MinNode node = mStack.top();
            mStack.pop();
            mCurrentMin = node.minBelow;
            // might not be "correct" but for convenience, pop returns what it popped
            return node;
        }

        // For testing
        std::vector<int> GetMinVector() const
        {
            std::vector<int> outVec(mStack.size());
            StackMin stackCopy(*this);
            unsigned int index = 0;
            while(!stackCopy.Empty())
            {
                outVec[index++] = stackCopy.Min();
                stackCopy.Pop();
            }

            return outVec;
        }

    private: 
        int mCurrentMin;
};

DEF_TESTDATA(StackMinData, StackMin, std::vector<int>);


static std::vector<int> TestStackMin(StackMin& inputStack)
{
    return inputStack.GetMinVector();
}

int Cci::Run_3_2()
{
    const unsigned int kNumTestCases = 6; 
    StackMinData testCases[kNumTestCases] = {
    // Set up so L -> R is top -> bot order of stack
        {{{1, 3, 2}},                       {1, 2, 2}},
        {{{-1, 3, -2, 7, 10, 8}},           {-2, -2, -2, 7, 8, 8}},
        {{{1, 2, 3, 4, 3, 4, 5, 7, 5}},     {1, 2, 3, 3, 3, 4, 5, 5, 5}},
        {{{3, 6, 5, 2, 3, 4, 5, 1, 2}},     {1, 1, 1, 1, 1, 1, 1, 1, 2}},
        {{{3, 3, 4, 4, 5, 5, 6, 6, 5}},     {3, 3, 4, 4, 5, 5, 5, 5, 5}},
        {{{}},                              {}}
    };
        
    return TestRunner::RunTestCases<StackMin, std::vector<int>, kNumTestCases>(testCases, &TestStackMin);
}
