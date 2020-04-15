#include <stack>
#include <vector> //for construction with initializer list
#include <algorithm> //so I can reverse the vector so it is more intuitive to initialize
#include <iostream>

class Stack 
{
    public:
        Stack(std::vector<int> d) 
        {
            std::reverse(d.begin(), d.end());
            for(auto it = d.begin(); it != d.end(); ++it)
            {
                mStack.push(*it);
            }
        }
        
        bool operator==(Stack other)
        {
            Stack aCopy(*this);
            Stack bCopy(other);
            while(!aCopy.Empty())
            {
                if(aCopy.Pop() != bCopy.Pop())
                {
                    return false;
                }
            }
            
            return true;
        }
        
        bool operator!=(Stack other)
        {
            return !(*this == other);
        }
        
        friend std::ostream& operator<<(std::ostream& os, Stack a);

        //For the most part im always gonna want top when i pop
        int Pop() { int val = mStack.top(); mStack.pop(); return val; }
        int Push(int val) { mStack.push(val); }
        int Top() { return mStack.top(); }
        bool Empty() { return mStack.empty(); }
        
    private:
        std::stack<int> mStack;
        
};

std::ostream& operator<<(std::ostream& os, Stack a)
{
    Stack copy(a);
    while(!copy.Empty())
    {
        os << copy.Pop();
    }
    
    return os;
}
