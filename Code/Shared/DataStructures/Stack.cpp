#include "Stack.h"

Stack::Stack(std::vector<int> d)
{
    std::reverse(d.begin(), d.end());
    for (auto it = d.begin(); it != d.end(); ++it)
    {
        mStack.push(*it);
    }
}

bool Stack::operator==(Stack other)
{
    Stack aCopy(*this);
    Stack bCopy(other);
    while (!aCopy.Empty())
    {
        if (aCopy.Pop() != bCopy.Pop())
        {
            return false;
        }
    }

    return true;
}

bool Stack::operator!=(Stack other)
{
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, Stack a)
{
    Stack copy(a);
    while (!copy.Empty())
    {
        os << copy.Pop();
    }

    return os;
}
