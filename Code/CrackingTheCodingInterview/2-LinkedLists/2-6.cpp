// 2.6 Palindrome - p95
//
// Implement a function to check if a linked list is a palindrome
//
// 0 - 1 - 2 - 2 - 1 - 0 is a palindrome 
//

#include "../../Shared/Testing/TestRunner.h"
#include "../../Shared/DataStructures/LinkedList.h"
#include "../CrackingTheCodingInterview.h"
#include "../../Shared/DataStructures/Stack.h"


DEF_TESTDATA(IsPalindromeData, LinkedList, bool);

static bool IsPalindrome(LinkedList& ll)
{
    std::vector<int> llValues;
    LinkedList::Node* pNode = ll.GetHead();

    // Empty lists and lists of size 1 are palindromes
    if(pNode == nullptr || pNode->pNext == nullptr)
    {
        return true;
    }  
    else 
    {
        // Get all the LL values
        while(pNode != nullptr)
        {
            llValues.push_back(pNode->data);
            pNode = pNode->pNext;
        }

        // Integer division on purpose, skip middle element for odd sized
        for(int i = 0; i < llValues.size() / 2; ++i)
        {
            // check from the edges inward 
            if(llValues[i] != llValues[llValues.size() - (i + 1)])
            {
                return false;
            }
        }

        return true;
    }
}

//
// Book Soln Superior to mine 
//  My soln goes over the entire list , then half the list again 
//  Book idea below only needs to go over the list once 
//
static bool IsPalindromeIterative(LinkedList& ll)
{
    Stack firstHalf({});
    LinkedList::Node* pNode = ll.GetHead();
    // Advance by two nodes each time to determine when you've made 
    // it halfway through the list
    LinkedList::Node* pDoubleSpeedNode = pNode;

    // Empty lists and lists of size 1 are still palindromes
    if (pNode == nullptr || pNode->pNext == nullptr)
    {
        return true;
    }
    else 
    {
        // Go through the first half, pushing node data to stack 
        // and detecting the half point by advancing at double speed
        while(pDoubleSpeedNode != nullptr && pDoubleSpeedNode->pNext != nullptr)
        {
            firstHalf.Push(pNode->data);
            pNode = pNode->pNext;
            pDoubleSpeedNode = pDoubleSpeedNode->pNext->pNext;
        }

        // If there's still 1 node remaining unhandled from double, was odd 
        // amount of elements, just skip past the middle element 
        if(pDoubleSpeedNode != nullptr)
        {
            pNode = pNode->pNext;
        }

        // Finish going through the second half, checking for palindrome with stack
        while (pNode != nullptr)
        {
            if(firstHalf.Pop() != pNode->data)
            {
                return false;
            }
            else 
            {
                pNode = pNode->pNext;
            }
        }

        return true;
    }
}

int Cci::Run_2_6()
{
    const unsigned kNumTestCases = 8;
    IsPalindromeData testCases[kNumTestCases] = 
    {
        {{{1, 1}},                      true},
        {{{1, 2, 3, 2, 1}},             true},
        {{{1, 2, 2, 1}},                true},
        {{{1, 2}},                      false},
        {{{1, 2, 3, 4, 2, 1}},          false},
        {{{1, 2, 4, 3, 3, 2, 1}},       false},
        {{{1}},                         true},
        {{{}},                          true},
    };

    int numFailed = TestRunner::RunTestCases<LinkedList, bool, kNumTestCases>(testCases, &IsPalindrome);
    numFailed += TestRunner::RunTestCases<LinkedList, bool, kNumTestCases>(testCases, &IsPalindromeIterative);

    return numFailed;
}
