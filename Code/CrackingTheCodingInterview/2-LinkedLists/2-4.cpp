// 2.4 Partition - pg 94 

// Given value X, reorganize the list such that all nodes less than X 
// come before all nodes greater than or equal to X . If X is in the list, it 
// can appear anywhere in the "right partition" 

#include "../../Shared/Testing/TestRunner.h"
#include "../CrackingTheCodingInterview.h"
#include "../../Shared/DataStructures/LinkedList.h"
#include <cassert>

struct PartitionParam
{
    PartitionParam(std::vector<int> linkedListData, int partitionVal) :
        l(linkedListData), val(partitionVal) {}
    LinkedList l;
    int val;
};

DEF_TESTDATA(PartitionData, PartitionParam, LinkedList)


static LinkedList Partition(PartitionParam& p)
{
    LinkedList::Node* pPrev = p.l.GetHead();
    if(pPrev == nullptr)
    {
        return p.l;
    }

    LinkedList::Node* pCur = pPrev->pNext;
    while(pCur != nullptr)
    {
        // If find a node less than partition, stitch up the list 
        // to remove and push it to the front of the list 
        if(pCur->data < p.val)
        {
            pPrev->pNext = pCur->pNext;
            p.l.PushFront(pCur);
            pCur = pPrev->pNext;
        }
        else 
        {
            pPrev = pCur;
            pCur = pCur->pNext;
        }
    }

    return p.l;
}

int Cci::Run_2_4()
{
    const unsigned int kNumTestCases = 8; 

    // Question allows left partition values to be in any order but this enforces 
    // the order I expect knowing how I solved the problem 
    PartitionData testCases[kNumTestCases] = {
        {{{1, 2, 3},                 2},        {{1, 2, 3}}},
        {{{3, 2, 1},                 2},        {{1, 3, 2}}},
        {{{},                        2},        {{}}},
        {{{1},                       2},        {{1}}},
        {{{2, 7, 3, 1, 4, 5, 6},     2},        {{{1, 2, 7, 3, 4, 5, 6}}}},
        {{{2, 7, 3, 1, 4, 5, 6},     4},        {{{1, 3, 2, 7, 4, 5, 6}}}},
        {{{2, 7, 3, 1, 4, 5, 6},     6},        {{{5, 4, 1, 3, 2, 7, 6}}}},
        {{{2, 7, 3, 1, 4, 5, 6},     8},        {{{6, 5, 4, 1, 3, 7, 2}}}}
    };
    
    return TestRunner::RunTestCases<PartitionParam, LinkedList, kNumTestCases>(testCases, &Partition);
}

