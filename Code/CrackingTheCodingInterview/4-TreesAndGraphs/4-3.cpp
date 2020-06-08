// 4.3 List of Depths - pg 109
// Given a binary tree, design an algo which rerturns a link lists of nodes at each depth 
// D linked lists for a tree with depth D 

#include "../../Shared/Testing/TestRunner.h"
#include "../CrackingTheCodingInterview.h"
#include "../../Shared/DataStructures/LinkedList.h"
#include "../../Shared/DataStructures/BinaryTree.h"

DEF_TESTDATA(DepthData, BinaryTree, std::vector<LinkedList>);

static void GetDepthsImpl(BinaryTree::Node* n, int depth, std::vector<LinkedList>& out)
{
    if(!n)
    {
        return;
    }
    
    out[depth].PushBack(n->data);
    depth += 1;
    
    GetDepthsImpl(n->pLeft, depth, out);
    GetDepthsImpl(n->pRight, depth, out);
}

static std::vector<LinkedList> GetDepths(BinaryTree& bt)
{
    std::vector<LinkedList> output;
    //probably not ideal to call height, could instead check if size greater than depth and push back
    output.resize(bt.Height());
    GetDepthsImpl(bt.GetRoot(), 0, output);
    return output;
}

int Cci::Run_4_3()
{
    const unsigned int kNumTestCases = 5;
    DepthData testCases[kNumTestCases] = {
        {{{{1, 2, 3, 4, 5, 6}},             3},                                     {{{1}},{{2,5}},{{3,4,6}}}},
        {{{{4, 2, 1, 3, 6, 5, 7}},          3},                                     {{{4}},{{2,6}},{{1,3,5,7}}}},
        {{{{1, 2, 3, 4, 5, 6, 7}},          3,  BinaryTree::Traversal_InOrder},     {{{4}},{{2,6}},{{1,3,5,7}}}},     
        {{{{1, 3, 2, 5, 7, 6, 4}},          3,  BinaryTree::Traversal_PostOrder},   {{{4}},{{2,6}},{{1,3,5,7}}}},
        {{{{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}},6},                                     {{{1}},{{2}},{{3}},{{4}},{{5,8}},{{6,7,9,10}}}}
    };
    
    return TestRunner::RunTestCases<BinaryTree, std::vector<LinkedList>, kNumTestCases>(testCases, &GetDepths);
}
