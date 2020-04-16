#include <iostream>
#include <vector>
#include <cassert>
#include <string>

class BinaryTree  
{
    public:
        enum Traversal
        {
            Traversal_PreOrder = 0,
            Traversal_InOrder = 1,
            Traversal_PostOrder = 2,
            Traversal_Count = 3
        };
    
        struct Node
        {
            Node(int val) : data(val), pLeft(nullptr), pRight(nullptr) {}
            int data;
            Node* pLeft;
            Node* pRight; 
        };
    
        BinaryTree(std::vector<int> initData, int maxDepth, Traversal t = Traversal_PreOrder);
        ~BinaryTree();
        BinaryTree(const BinaryTree& bt);
        BinaryTree& operator=(const BinaryTree& bt);

        inline Node* GetRoot() { return mpRoot; }
        inline const Node* GetRoot() const { return mpRoot; } 
        
        int Height() const;
        
        friend std::ostream& operator<<(std::ostream& os, const BinaryTree& tree);
        
    private:
        Node* mpRoot = nullptr; 
        std::vector<int> mData; //For easy info printing
        const Traversal mBuildTraversal;
        
        Node* BuildTree(std::vector<int> data, uint32_t& dataIndex, 
            int curDepth, int maxDepth, uint32_t& unassignedParents);
        
        void CopyTree(const BinaryTree& bt);
        
        Node* CopyTreeImpl(const Node* pOther);
        
        //Does post order delete 
        void FreeTree(Node* pNode);
};

std::ostream& operator<<(std::ostream& os, const BinaryTree& tree);