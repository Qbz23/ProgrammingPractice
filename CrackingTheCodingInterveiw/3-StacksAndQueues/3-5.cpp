// 3.5 Sort Stack - p 99

// write a program to sort a stack st smallest on top. 
// Can use a temp stack but not a different data structure 
// stack can push pop peek and isEmpty. top == peek  

#include "iStack.hpp"
#include "../../Shared/TestRunner.hpp"

iStack sortStack(iStack inputStack)
{
    if(inputStack.empty())
        return inputStack;
    
    //Pop off top of input stack 
    //Put it on the second stack 
    //for remaining input 
    //pop off
    //If pop'd is smaller, push to second 
    //If pop'd is bigger, hold other in temp 
    //If pop'd is bigger than next, push temp to original stack and hold next other in temp 
    
    iStack outputStack = iStack(std::vector<int>());
    //Start by putting first in other
    outputStack.push(inputStack.pop());
    while(!inputStack.empty())
    {
        int val = inputStack.pop(); 
        if(val <= outputStack.top())
        {
            outputStack.push(val);
        }
        else
        {
            int temp = outputStack.pop();
            //Pop stuff off the output stack till you find something bigger this can go on top of 
            while(!outputStack.empty() && val > outputStack.top())
            {
                inputStack.push(temp);
                temp = outputStack.pop();
            }
            outputStack.push(val);
            outputStack.push(temp);
        }
    }
    
    return outputStack;
}

DEF_TESTDATA(SortStackData, iStack, iStack); 

int main()
{
    const unsigned int kNumTestCases = 5; 
    SortStackData testCases[kNumTestCases] = {
        {{{1, 2, 4, 3}},                {{1, 2, 3, 4}}},
        {{{4, 3, 2, 1}},                {{1, 2, 3, 4}}},
        {{{9, 3, 7, 8, 1, 6, 2, 4, 5}}, {{1, 2, 3, 4, 5, 6, 7, 8, 9}}},
        {{{1, 1, 1, 5, 3, 5, 3, 3, 4}}, {{1, 1, 1, 3, 3, 3, 4, 5, 5}}},
        {{{}},                          {{}}}};
        
        
    testRunner::runTests<iStack, iStack, kNumTestCases>(testCases, &sortStack);
}
