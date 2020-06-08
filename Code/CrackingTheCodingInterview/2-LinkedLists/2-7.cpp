// 2.7 Intersection - p95
//
// Given two singly linked lists, determine if they intersect 
// and return the intersecting node. Note this is based on reference, not value
//

#include "../../Shared/Testing/TestRunner.h"
#include "../../Shared/DataStructures/LinkedList.h"
#include "../CrackingTheCodingInterview.h"
#include <cassert>

struct IntersectionParam
{
    IntersectionParam(std::vector<int> linkedListData1, std::vector<int> linkedListData2, int intersectionNode) :
        l1(linkedListData1), l2(linkedListData2), intersection(intersectionNode) {}
    LinkedList l1;
    LinkedList l2;
    int intersection;
};

DEF_TESTDATA(IntersectionData, IntersectionParam, bool);

//
// Although this wants comparison by reference I just did by value 
// Creating intersecting linked lists is doing weird stuff to my linked 
// list class but it doesn't seem like that's something I would generally 
// want to support. As long as the data values are unique, its effectively the 
// same test. The question wouldn't  require you to create the intersecting 
// list, just handle it after it's been passed to you
//
static LinkedList::Node* IntersectionImpl(LinkedList& ll1, LinkedList& ll2)
{
    // Start by advancing to the back of both lists 
    LinkedList::Node* pNode1 = ll1.GetHead();
    int listLength1 = 1; // tail wont be counted in loop
    while(pNode1->pNext != nullptr)
    {
        listLength1 += 1;
        pNode1 = pNode1->pNext;
    }

    LinkedList::Node* pNode2 = ll2.GetHead();
    int listLength2 = 1;
    while (pNode2->pNext != nullptr)
    {
        listLength2 += 1;
        pNode2 = pNode2->pNext;
    }

    // If they combine into a single branch through an intersection, 
    // their tails must be the same
    if(pNode1->data != pNode2->data)
    {
        return nullptr;
    }

    LinkedList::Node* pWalker1 = ll1.GetHead();
    LinkedList::Node* pWalker2 = ll2.GetHead();
    // If one list longer than the other, chop off its front nodes 
    // their back half must be the same so if there are extra nodes 
    // explaining the difference in sizes they must be at the front 
    if(listLength2 > listLength1)
    {
        int advanceAmount = listLength2 - listLength1;
        int advanceCounter = 0;
        while(advanceCounter++ < advanceAmount)
        {
            pWalker2 = pWalker2->pNext;
        }
    }
    else if(listLength1 > listLength2)
    {
        int advanceAmount = listLength1 - listLength2;
        int advanceCounter = 0;
        while (advanceCounter++ < advanceAmount)
        {
            pWalker1 = pWalker1->pNext;
        }
    }

    // Now both lists are functionally the same size, the intersecting 
    // is the first shared node among the two lists 
    while(pWalker1 != nullptr && pWalker2 != nullptr)
    {
        if(pWalker1->data == pWalker2->data)
        {
            return pWalker1;
        }
        else 
        {
            pWalker1 = pWalker1->pNext;
            pWalker2 = pWalker2->pNext;
        }
    }

    // should not get here
    assert(false);
    return nullptr;
}

static bool Intersection(IntersectionParam& p)
{
    LinkedList::Node* pLL2Tail = nullptr;
    // If an intersection is desired, create it here
    if(p.intersection != -1)
    {
        //
        // l2 is the "branch" of l1 preceding the intersection
        // ex:
        //      L1 = 1 2 3 
        //      L2 = 4 5 
        //      interection = 1 
        //
        //      1 -------\
        //                2 -> 3
        //      4 -> 5 --/
        //
        
        // Find start of intersection in l1 
        LinkedList::Node* pNode1 = p.l1.GetHead();
        int counter = 0;
        while(counter++ < p.intersection)
        {
            pNode1 = pNode1->pNext;
        }
        
        // Save initial tail of ll2 to restore it later
        LinkedList::Node* pNode2 = p.l2.GetHead();
        while(pNode2->pNext != nullptr)
        {
            pNode2  = pNode2->pNext;
        }
        pLL2Tail = pNode2;

        assert(pNode1 != nullptr);
        // Now insert the intersection and everything past it at the end of l2
        while(pNode1 != nullptr)
        {
            p.l2.PushBack(pNode1->data);
            pNode1 = pNode1->pNext;
        }
    }

    LinkedList::Node* resultNode = IntersectionImpl(p.l1, p.l2);
    if(p.intersection != -1)
    {
        assert(resultNode != nullptr);
        assert(pLL2Tail != nullptr);
        bool matches = resultNode->data == pLL2Tail->pNext->data;
        return matches;
    }
    else 
    {
        return resultNode == nullptr;
    }
}

int Cci::Run_2_7()
{
    const unsigned kNumTestCases = 9;

    // Expect true for every case, output checked by calling function
    IntersectionData testCases[kNumTestCases] =
    {
        {{{{1, 2}},         {{3, 4}},           1},        true},
        {{{{1, 2}},         {{3, 4}},          -1},        true},
        {{{{1, 2, 3, 4}},   {{5, 6}},          -1},        true},
        {{{{1, 2, 3, 4}},   {{5, 6}},           1},        true},
        {{{{1, 2, 3, 4}},   {{5, 6}},           2},        true},
        {{{{1, 2, 3, 4}},   {{5, 6}},           3},        true},
        {{{{1, 2, 3, 4}},   {{5, 6}},          -1},        true},
        {{{{1, 2}},         {{3, 4, 5, 6}},     1},        true},
        {{{{1, 2}},         {{3, 4, 5, 6}},    -1},        true},
    };

    return TestRunner::RunTestCases<IntersectionParam, bool, kNumTestCases>(testCases, &Intersection);
}

