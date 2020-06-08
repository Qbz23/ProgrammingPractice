// 2.5 Sum Lists - pg 95

// Two numbers are represented as a linked list with each node being a 
// digit's value. Sum them and return a list in the same representation 

#include "../../Shared/Testing/TestRunner.h"
#include "../CrackingTheCodingInterview.h"
#include "../../Shared/DataStructures/LinkedList.h"
#include <cassert>

struct SumListsParam
{
    SumListsParam(std::vector<int> linkedListData1, std::vector<int> linkedListData2) :
        l1(linkedListData1), l2(linkedListData2) {}
    LinkedList l1;
    LinkedList l2;
};

DEF_TESTDATA(SumListsData, SumListsParam, LinkedList)


static LinkedList SumLists(SumListsParam& p)
{
    LinkedList output;
    LinkedList::Node* pNode1 = p.l1.GetHead();
    LinkedList::Node* pNode2 = p.l2.GetHead();
    // If a list is empty, just return the other list
    if(pNode1 == nullptr)
    {
        return p.l2;
    }
    else if(pNode2 == nullptr)
    {
        return p.l1;
    }

    // Iterate over both lists 
    bool carry = false;
    while(pNode1 != nullptr || pNode2 != nullptr)
    {
        int val;
        // List1 is done
        if(pNode1 == nullptr)
        {
            // Add 2 only 
            val = pNode2->data + (int)carry;
            carry = false;
            pNode2 = pNode2->pNext;
        }
        // List2 is done 
        else if(pNode2 == nullptr)
        {
            // Add 1 only
            val = pNode1->data + (int)carry;
            carry = false;
            pNode1 = pNode1->pNext;
        }
        // Both lists still being used 
        else 
        {
            // Add 1 and 2 
            val = pNode1->data + pNode2->data + (int)carry;
            carry = false;
            if(val >= 10)
            {
                carry = true;
                val %= 10;
            }
            pNode1 = pNode1->pNext;
            pNode2 = pNode2->pNext;
        }

        output.PushBack(val);
    }

    if(carry)
    {
        output.PushBack(1);
    }

    return output;
}

int Cci::Run_2_5()
{
    const unsigned int kNumTestCases = 11; 

    SumListsData testCases[kNumTestCases] = {
        {{{1, 2, 3},                    {1}},                   {{2, 2, 3}}},
        {{{1},                          {1, 2, 3}},             {{2, 2, 3}}},
        {{{1},                          {}},                    {{1}}},
        {{{},                           {1}},                   {{1}}},
        {{{},                           {}},                    {{}}},
        {{{1, 2, 3},                    {9}},                   {{0, 3, 3}}},
        {{{9},                          {1, 2, 3}},             {{0, 3, 3}}},
        {{{1, 2, 3, 4, 5},              {9, 7, 6, 5, 4}},       {{0, 0, 0, 0, 0, 1}}},
        {{{9, 7, 6, 5, 4},              {1, 2, 3, 4, 5}},       {{0, 0, 0, 0, 0, 1}}},
        {{{1, 2, 2, 5, 5},              {9, 7, 6, 5, 4}},       {{0, 0, 9, 0, 0, 1}}},
        {{{9, 7, 6, 5, 4},              {1, 2, 2, 5, 5}},       {{0, 0, 9, 0, 0, 1}}}
    };
    
    return TestRunner::RunTestCases<SumListsParam, LinkedList, kNumTestCases>(testCases, &SumLists);
}

