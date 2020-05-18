#include <stack>
#include <vector> //for construction with initializer list
#include <algorithm> //so I can reverse the vector so it is more intuitive to initialize
#include <iostream>

template <typename T >
class Stack
{
    public: 
        // either child inits mStack or an empty stack is desired 
        Stack() {}

        Stack(std::vector<T> d, bool topToBot = true)
        {
            if(topToBot)
            {
                std::reverse(d.begin(), d.end());
            }

            for (auto it = d.begin(); it != d.end(); ++it)
            {
                mStack.push(*it);
            }
        }

        virtual bool operator<(const Stack<T>& other) const
        {
            return !(*this == other);
        }

        virtual bool operator==(const Stack<T>& other) const
        {
            Stack<T> aCopy(*this);
            Stack<T> bCopy(other);

            if(aCopy.Size() != bCopy.Size())
            {
                return false;
            }

            while (!aCopy.Empty())
            {
                if (!bCopy.Empty() && !(aCopy.Pop() == bCopy.Pop()))
                {
                    return false;
                }
            }

            return true;
        }

        virtual bool operator!=(Stack<T> other) const
        {
            return !(*this == other);
        }

        //For the most part im always gonna want top when i pop
        virtual inline T Pop() { T val = mStack.top(); mStack.pop(); return val; }
        virtual inline void Push(T val) { mStack.push(val); }
        virtual inline T Top() const { return mStack.top(); }
        virtual inline bool Empty() const { return mStack.empty(); }
        virtual inline size_t Size() const { return mStack.size(); }

        friend std::ostream& operator<<(std::ostream& os, Stack<T> a)
        {
            Stack<T> copy(a);
            while (!copy.Empty())
            {
                os << copy.Pop();
            }

            return os;
        }

    protected:
        std::stack<T> mStack;
};       
