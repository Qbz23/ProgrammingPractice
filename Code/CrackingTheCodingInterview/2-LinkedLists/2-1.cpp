// 2.2 Remove Dupes - pg 94 

// Remove duplicate from an unsorted linked list

#include "../../Shared/Testing/TestRunner.h"
#include "../CrackingTheCodingInterview.h"
#include "../../Shared/DataStructures/LinkedList.h"
#include <unordered_set>

DEF_TESTDATA(RemoveDupesData, LinkedList, LinkedList)

// Delete pCur from the list, advanvces pCur to next
static void DeleteNode(LinkedList::Node*& pPrev, LinkedList::Node*& pCur)
{
    pPrev->pNext = pCur->pNext;
    delete pCur;
    pCur = pPrev->pNext;
}

static LinkedList RemoveDupes(LinkedList& l)
{
    // Keep track of what you've found 
    std::unordered_set<int> foundValues;

    // Early out if empty list
    LinkedList::Node* pPrev = l.GetHead();
    if (pPrev == nullptr)
    {
        return l;
    }
    foundValues.emplace(pPrev->data);
    // Iterate over list
    LinkedList::Node* pCur = pPrev->pNext;
    while(pCur != nullptr)
    {
        // List already contains pCur's data, it's a duplicate
        if(foundValues.find(pCur->data) != foundValues.end())
        {
            DeleteNode(pPrev, pCur);
        }
        else 
        {
            // unique value, add it to set 
            foundValues.emplace(pCur->data);
            pPrev = pCur;
            pCur = pCur->pNext;
        }
    }

    return l;
}

// Much slower, just goes over the list O(N^2)
static LinkedList RemoveDupesNoExtraStorage(LinkedList& l)
{
    LinkedList::Node* pPrev = l.GetHead();
    if (pPrev == nullptr)
    {
        return l;
    }
    
    LinkedList::Node*& pCheckNode = pPrev;
    // For each node
    while(pCheckNode != nullptr)
    {
        // Check every remaining node for this node's data
        LinkedList::Node* pCur = pCheckNode->pNext;
        while (pCur != nullptr)
        {
            if (pCheckNode->data == pCur->data)
            {
                DeleteNode(pPrev, pCur);
            }
            else 
            {
                pPrev = pCur;
                pCur = pCur->pNext;
            }
        }

        pCheckNode = pCheckNode->pNext;
    }

    return l;
}

int Cci::Run_2_1()
{
    const unsigned int kNumTestCases = 7; 

    RemoveDupesData testCases[kNumTestCases] = {
        {{{}},                                      {{}}},
        {{{1}},                                     {{1}}},
        {{{1, 2, 3}},                               {{1, 2, 3}}},
        {{{1, 2, 3, 3, 2}},                         {{1, 2, 3}}},
        {{{2, 1, 2, 1, 1, 1, 3, 5, 3, 2, 4, 7, 5}}, {{2, 1, 3, 5, 4, 7}}},
        {{{1, 2, 2, 1, 1, 1, 5, 3, 3, 2, 4, 5, 7}}, {{1, 2, 5, 3, 4, 7}}},
        {{{5, 1, 1, 2, 1, 3, 5, 2, 3, 7, 4, 5, 7}}, {{5, 1, 2, 3, 7, 4}}}
    };
    
    uint32_t testCaseFails = 0;
    testCaseFails = TestRunner::RunTestCases<LinkedList, LinkedList, kNumTestCases>(testCases, &RemoveDupes);
    testCaseFails += TestRunner::RunTestCases<LinkedList, LinkedList, kNumTestCases>(testCases, &RemoveDupesNoExtraStorage);
    return testCaseFails;
}
