#include "LinkedList.h"
#include <vector>
#include <iostream>

LinkedList::LinkedList(std::vector<int> data)
{
    mpHead = new Node(data[0]);
    Node* pCurrent = mpHead;
    for(int i = 1; i < data.size(); ++i)
    {
        Node* pNew = new Node(data[i]);
        pCurrent->pNext = pNew; 
        pCurrent = pNew; 
    }
}

LinkedList::~LinkedList()
{
    Node* pCurrent = mpHead;
    while (pCurrent != nullptr)
    {
        Node* deadNode = pCurrent;
        pCurrent = pCurrent->pNext;
        delete deadNode;
    }
}

LinkedList::LinkedList(const LinkedList& l)
{
    CopyImpl(l);
}

LinkedList& LinkedList::operator=(const LinkedList& l)
{
    CopyImpl(l);
    return *this;
}

void LinkedList::Push(int d)
{
    if (!mpHead)
    {
        mpHead = new Node(d);
    }
    else
    {
        Node* cur = mpHead;
        while (cur->pNext != nullptr)
        {
            cur = cur->pNext;
        }
        cur->pNext = new Node(d);
    }
}

bool LinkedList::operator==(const LinkedList other) const
{
    const Node* pCur = mpHead;
    const Node* pCurOther = other.GetHead();

    while (pCur)
    {
        if (!pCurOther || (pCur->data != pCur->data))
        {
            return false;
        }
        else
        {
            pCur = pCur->pNext;
            pCurOther = pCurOther->pNext;
        }
    }

    return pCurOther == nullptr;
}

void LinkedList::CopyImpl(const LinkedList& l)
{
    const Node* lHead = l.GetHead();
    const Node* pCurrent = lHead->pNext;
    mpHead = new Node(lHead->data);
    Node* pSelf = mpHead;
    while (pCurrent != nullptr)
    {
        Node* newNode = new Node(pCurrent->data);
        pCurrent = pCurrent->pNext;
        pSelf->pNext = newNode;
        pSelf = newNode;
    }
}

std::ostream& operator<<(std::ostream& os, LinkedList ll)
{
    LinkedList::Node* cur = ll.GetHead();
    while (cur)
    {
        os << cur->data << ", ";
        cur = cur->pNext;
    }

    return os;
}
