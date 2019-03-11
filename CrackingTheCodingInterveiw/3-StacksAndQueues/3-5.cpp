// 3.5 Sort Stack - p 99

// write a program to sort a stack st smallest on top. 
// Can use a temp stack but not a different data structure 
// stack can push pop peek and isEmpty. top == peek  

#include "../../Shared/TestRunner.hpp"
#include "../../Shared/DataStructures/Stack.hpp"

Stack sortStack(Stack& inputStack)
{
    if(inputStack.Empty())
        return inputStack;
    
    //Pop off top of input stack 
    //Put it on the second stack 
    //for remaining input 
    //pop off
    //If pop'd is smaller, push to second 
    //If pop'd is bigger, hold other in temp 
    //If pop'd is bigger than next, push temp to original stack and hold next other in temp 
    
    Stack outputStack = Stack(std::vector<int>());
    //Start by putting first in other
    outputStack.Push(inputStack.Pop());
    while(!inputStack.Empty())
    {
        int val = inputStack.Pop(); 
        if(val <= outputStack.Top())
        {
            outputStack.Push(val);
        }
        else
        {
            int temp = outputStack.Pop();
            //Pop stuff off the output stack till you find something bigger this can go on top of 
            while(!outputStack.Empty() && val > outputStack.Top())
            {
                inputStack.Push(temp);
                temp = outputStack.Pop();
            }
            outputStack.Push(val);
            outputStack.Push(temp);
        }
    }
    
    return outputStack;
}

DEF_TESTDATA(SortStackData, Stack, Stack); 

int main()
{
    const unsigned int kNumTestCases = 5; 
    SortStackData testCases[kNumTestCases] = {
        {{{1, 2, 4, 3}},                {{1, 2, 3, 4}}},
        {{{4, 3, 2, 1}},                {{1, 2, 3, 4}}},
        {{{9, 3, 7, 8, 1, 6, 2, 4, 5}}, {{1, 2, 3, 4, 5, 6, 7, 8, 9}}},
        {{{1, 1, 1, 5, 3, 5, 3, 3, 4}}, {{1, 1, 1, 3, 3, 3, 4, 5, 5}}},
        {{{}},                          {{}}}};
        
        
    testRunner::runTests<Stack, Stack, kNumTestCases>(testCases, &sortStack);
}
