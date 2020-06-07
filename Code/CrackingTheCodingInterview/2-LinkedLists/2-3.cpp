// 2.3 Delete middle node - pg 94 

// Given a node that is neither the head nor tail, not necssarily the exact 
// middle, delete this node without access to the list itself 

#include "../../Shared/Testing/TestRunner.h"
#include "../CrackingTheCodingInterview.h"
#include "../../Shared/DataStructures/LinkedList.h"
#include <cassert>

struct DeleteMiddleTestParam
{
    DeleteMiddleTestParam(std::vector<int> linkedListData, int deleteNodeIndex) : 
        l(linkedListData), nodeToDelete(deleteNodeIndex) {}
    LinkedList l;
    uint32_t nodeToDelete;
};

DEF_TESTDATA(DeleteMiddleData, DeleteMiddleTestParam, LinkedList)

static void DeleteMiddleImpl(LinkedList::Node* pNode)
{
    // We can't delete this specific node b/c itll break our list 
    // So the idea here is to transform this to next and delete next 
    // Say we have A -> B -> C -> D, and we're given B to remove 
    // We need to get to A -> C -> D only by modifying B 
    // We can set deleted node's data to next A -> C -> C-> D 
    // And then effectively delete the next by advancing next ptr
    LinkedList::Node* pDeadNode = pNode->pNext;
    pNode->data = pDeadNode->data;
    pNode->pNext = pDeadNode->pNext;
    delete pDeadNode;
}

static LinkedList DeleteMiddle(DeleteMiddleTestParam& p)
{
    assert(p.nodeToDelete != 0);
    LinkedList::Node* pNode = p.l.GetHead();
    uint32_t counter = 0;
    while(pNode != nullptr)
    {
        if(counter == p.nodeToDelete)
        {
            assert(pNode->pNext != nullptr);
            DeleteMiddleImpl(pNode);
            return p.l;
        }
        else 
        {
            counter += 1;
            pNode = pNode->pNext;
        }
    }

    // Should not get here
    assert(false);
    return p.l;
}

int Cci::Run_2_3()
{
    const unsigned int kNumTestCases = 5; 

    DeleteMiddleData testCases[kNumTestCases] = {
        {{{1, 2, 3},                 1},      {{1, 3}}},
        {{{1, 2, 3, 4},              2},      {{1, 2, 4}}},
        {{{1, 2, 3, 4, 5},           1},      {{1, 3, 4, 5}}},
        {{{1, 2, 3, 4, 5},           2},      {{1, 2, 4, 5}}},
        {{{1, 2, 3, 4, 5},           3},      {{1, 2, 3, 5}}}
    };
    
    return TestRunner::RunTestCases<DeleteMiddleTestParam, LinkedList, kNumTestCases>(testCases, &DeleteMiddle);
}
