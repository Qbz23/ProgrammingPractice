#include <stack>
#include <vector> //for construction with initializer list
#include <algorithm> //so I can reverse the vector so it is more intuitive to initialize
#include <iostream>

class Stack 
{
    public:
        Stack(std::vector<int> d);
        bool operator==(Stack other);
        bool operator!=(Stack other);
        
        friend std::ostream& operator<<(std::ostream& os, Stack a);

        //For the most part im always gonna want top when i pop
        inline int Pop() { int val = mStack.top(); mStack.pop(); return val; }
        inline void Push(int val) { mStack.push(val); }
        inline int Top() { return mStack.top(); }
        inline bool Empty() { return mStack.empty(); }
        
    private:
        std::stack<int> mStack;
};
