#include "../../Shared/DataStructures/BinaryTree.h"
#include "../OtherTests.h"
#include "../OtherTestsLogFlags.h"
#include "../../Shared/Logging/Logging.h"
#include <sstream>

//
// Will have a better more general system for testing data structures in the future 
// This isn't really a test as-is

int OtherTests::BinaryTreeConstruct()
{
    const uint32_t kNumTestTrees = 9;
    
    BinaryTree trees[kNumTestTrees] = {
        {{1, 2, 3, 4, 5, 6},                3},                                     //
        {{1, 2, 3, 4, 5, 6},                3,  BinaryTree::Traversal_InOrder},     // Indices
        {{1, 2, 3, 4, 5, 6},                3,  BinaryTree::Traversal_PostOrder},   //
        
        {{4, 2, 1, 3, 6, 5, 7},             3},                                     //
        {{1, 2, 3, 4, 5, 6, 7},             3,  BinaryTree::Traversal_InOrder},     // BST
        {{1, 3, 2, 5, 7, 6, 4},             3,  BinaryTree::Traversal_PostOrder},   //
        
        {{1, 2, 3, 4, 5, 6, 7, 8, 9, 10},   6},                                     //
        {{1, 2, 3, 4, 5, 6, 7, 8, 9, 10},   6,  BinaryTree::Traversal_InOrder},     // Lopsided
        {{1, 2, 3, 4, 5, 6, 7, 8, 9, 10},   6,  BinaryTree::Traversal_PostOrder}    //
    };
    
    for(uint32_t i = 0; i < kNumTestTrees; ++i)
    {
        std::stringstream ss;
        ss << trees[i];
        Log::If(OtherTestsLogFlags::bLogDataStructureTestsVerbose, ss.str());
    }

    return 0;
}
