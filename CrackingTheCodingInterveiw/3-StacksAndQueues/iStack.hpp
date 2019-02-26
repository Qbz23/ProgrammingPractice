#include <stack>
#include <vector> //for construction with initializer list
#include <algorithm> //so I can reverse the vector so it is more intuitive to initialize
#include <iostream>

class iStack 
{
    public:
        iStack(std::vector<int> d) 
        {
            std::reverse(d.begin(), d.end());
            for(auto it = d.begin(); it != d.end(); ++it)
            {
                mStack.push(*it);
            }
        }
        
        bool operator==(iStack other)
        {
            iStack aCopy(*this);
            iStack bCopy(other);
            while(!aCopy.empty())
            {
                if(aCopy.pop() != bCopy.pop())
                {
                    return false;
                }
            }
            
            return true;
        }
        
        bool operator!=(iStack other)
        {
            return !(*this == other);
        }
        
        friend std::ostream& operator<<(std::ostream& os, iStack a);

        //For the most part im always gonna want top when i pop
        int pop() { int val = mStack.top(); mStack.pop(); return val; }
        int push(int val) { mStack.push(val); }
        int top() { return mStack.top(); }
        bool empty() { return mStack.empty(); }
        
    private:
        std::stack<int> mStack;
        
};

std::ostream& operator<<(std::ostream& os, iStack a)
{
    iStack copy(a);
    while(!copy.empty())
    {
        os << copy.pop();
    }
    
    return os;
}
