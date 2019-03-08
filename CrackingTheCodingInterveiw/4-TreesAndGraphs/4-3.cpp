// 4.3 List of Depths - pg 109
// Given a binary tree, design an algo which rerturns a link lists of nodes at each depth 
// D linked lists for a tree with depth D 

#include "../../Shared/TestRunner.hpp"
#include "../2-LinkedLists/LinkedList.hpp"
#include "BinaryTree.hpp"

void getDepthsImpl(BinaryTree::Node* n, int depth, std::vector<LinkedList>& out)
{
    if(!n)
        return;
    
    out[depth].Push(n->data);
    depth += 1;
    
    getDepthsImpl(n->pLeft, depth, out);
    getDepthsImpl(n->pRight, depth, out);
}

DEF_TESTDATA(DepthData, BinaryTree, std::vector<LinkedList>);

std::vector<LinkedList> getDepths(BinaryTree& bt)
{
    DepthData dd(bt, std::vector<LinkedList>());
    //probably not ideal to call height, could instead check if size greater than depth and push back
    dd.expectedOutput.resize(dd.input.height());
    getDepthsImpl(dd.input.getRoot(), 0, dd.expectedOutput);
    return dd.expectedOutput;
}

int main()
{
    const unsigned int kNumTestCases = 2;
    //TODO when fix bt memory leak add more test cases 
    DepthData testCases[kNumTestCases] = {
        {{{{1, 2, 3, 4, 5, 6}},       3}, {{{1}},{{2,5}},{{3,4,6}}}},
        {{{{4, 2, 1, 3, 6, 5, 7}},    3}, {{{4}},{{2,6}},{{1,3,5,7}}}}
    };
    
    testRunner::runTests<BinaryTree, std::vector<LinkedList>, kNumTestCases>(testCases, &getDepths);
}