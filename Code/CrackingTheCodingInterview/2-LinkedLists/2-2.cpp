// 2.2 Return kth to last - pg 94 

// find the kth to last item in a singly linked list 

#include "../../Shared/Testing/TestRunner.h"
#include "../CrackingTheCodingInterview.h"
#include "../../Shared/DataStructures/LinkedList.h"

struct KToLastTestParam
{
    KToLastTestParam(std::vector<int> linkedListData, int _k) : l(linkedListData), k(_k) {}
    LinkedList l;
    int k;
};

DEF_TESTDATA(KToLastData, KToLastTestParam, int)

// Assert k >= 1 (first to last means last) 
// Also assumes length of linked list <= k
// A better world wouldnt have alloc here but its not the end of the world, 
// going after logic of the problems
static int kToLast(KToLastTestParam& p)
{
    LinkedList::Node* pCurrent = p.l.GetHead();
    int counter = 0;
    int* historyBuffer = new int[p.k];
    while(pCurrent != nullptr)
    {    
        int index = counter % p.k;
        counter += 1;
        historyBuffer[index] = pCurrent->data;
        pCurrent = pCurrent->pNext;
    }
    
    int adjustedIndex = (counter - p.k) % p.k;
    int result = historyBuffer[adjustedIndex];
    
    delete historyBuffer;    
    return result;
}

int Cci::Run_2_2()
{
    const unsigned int kNumTestCases = 4; 

    KToLastData testCases[kNumTestCases] = {
    {{{1, 2, 3, 4, 5, 6, 7, 8},                 1},     8},
    {{{1, 2, 3, 4, 5, 6, 7, 8},                 2},     7},
    {{{1, 2, 3, 4, 5, 6, 7, 8},                 4},     5},
    {{{9, 8, 4, 3, 2, 6, 1, 2, 9, 4, 6, 7, 12}, 6},     2}};
    
    return TestRunner::RunTestCases<KToLastTestParam, int, kNumTestCases>(testCases, &kToLast);
}
