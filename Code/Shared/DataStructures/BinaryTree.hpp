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
    
        BinaryTree(std::vector<int> initData, int maxDepth, Traversal t = Traversal_PreOrder) : mBuildTraversal(t)
        {
            uint32_t dataIndex = 0;
            uint32_t unassignedParents = 0;
            mpRoot = BuildTree(initData, dataIndex, 0, maxDepth, unassignedParents);
            assert(dataIndex == initData.size());
            //Just for debug printing
            mData = initData;
        }
        
        ~BinaryTree()
        {
            FreeTree(mpRoot);
        }
        
        BinaryTree(const BinaryTree& bt) : mBuildTraversal(Traversal_PreOrder)
        {
            CopyTree(bt);
        }
        
        BinaryTree& operator=(const BinaryTree& bt)
        {
            CopyTree(bt);
            return *this;
        }
        
        Node* GetRoot() { return mpRoot; }
        const Node* GetRoot() const { return mpRoot; } 
        
        int Height() const 
        {
            Node* pCur = mpRoot;
            int height = 0;
            //This assumes left will be longest which is safe w how this tree is built but not in general
            while(pCur != nullptr)
            {
                ++height;
                pCur = pCur->pLeft;
            }                
            
            return height;
        }
        
        friend std::ostream& operator<<(std::ostream& os, const BinaryTree& tree);
        
    private:
        Node* mpRoot = nullptr; 
        std::vector<int> mData; //For easy info printing
        const Traversal mBuildTraversal;
        
        Node* BuildTree(std::vector<int> data, uint32_t& dataIndex, 
            int curDepth, int maxDepth, uint32_t& unassignedParents)
        {
            if(curDepth == maxDepth || (dataIndex + unassignedParents == data.size()))
            {
                return nullptr;
            }
            else
            {
                Node* pNew = nullptr;
                Node* pLeft = nullptr;
                Node* pRight = nullptr;
                int nextDepth = ++curDepth;
                switch(mBuildTraversal)
                {
                    case Traversal_PreOrder:
                    {   
                        int val = data[dataIndex++];
                        pNew = new Node(val);
                        pLeft = BuildTree(data, dataIndex, nextDepth, maxDepth, unassignedParents);
                        pRight = BuildTree(data, dataIndex, nextDepth, maxDepth, unassignedParents);
                        break;
                    }
                    case Traversal_InOrder:
                    {
                        unassignedParents += 1;
                        pLeft = BuildTree(data, dataIndex, nextDepth, maxDepth, unassignedParents);
                        int val = data[dataIndex++];
                        pNew = new Node(val);
                        unassignedParents -= 1;
                        pRight = BuildTree(data, dataIndex, nextDepth, maxDepth, unassignedParents);
                        break;
                    }
                    case Traversal_PostOrder:
                    {                        
                        unassignedParents += 1;
                        pLeft = BuildTree(data, dataIndex, nextDepth, maxDepth, unassignedParents);
                        pRight = BuildTree(data, dataIndex, nextDepth, maxDepth, unassignedParents);
                        int val = data[dataIndex++];
                        pNew = new Node(val);
                        unassignedParents -= 1;
                        break;
                    }
                }
                
                pNew->pLeft = pLeft;
                pNew->pRight = pRight;
                return pNew;
            }
        }
        
        void CopyTree(const BinaryTree& bt)
        {
            mpRoot = CopyTreeImpl(bt.GetRoot());
            mData = bt.mData;
        }
        
        Node* CopyTreeImpl(const Node* pOther)
        {
            Node* pNew = new Node(pOther->data);
            if(pOther->pLeft)
            {
                pNew->pLeft = CopyTreeImpl(pOther->pLeft);
            }
            if(pOther->pRight)
            {
                pNew->pRight = CopyTreeImpl(pOther->pRight);
            }
            
            return pNew;
        }
        
        //Does post order delete 
        void FreeTree(Node* pNode)
        {
            if(pNode)
            {
                FreeTree(pNode->pLeft);
                FreeTree(pNode->pRight);
                delete pNode;
            }
        }
};

std::ostream& PrintNode(std::ostream& os, const BinaryTree::Node* pNode, uint32_t spaceCount)
{
    uint32_t kSpaceCountOffset = 4;
    if(pNode)
    {
        spaceCount += kSpaceCountOffset;
        
        //Right first b/c its on top
        PrintNode(os, pNode->pRight, spaceCount);
        
        //Self 
        os << std::endl;
        //Aplpy indent 
        for(uint32_t i = 0; i < spaceCount; ++i)
            os << " ";
        os << std::to_string(pNode->data) << std::endl;
        
        //Left
        PrintNode(os, pNode->pLeft, spaceCount);
    }
    
    return os;
}

std::ostream& operator<<(std::ostream& os, const BinaryTree& tree)
{
    os << "{{";
    for(uint32_t i = 0; i < tree.mData.size(); ++i)
    {
        os << std::to_string(tree.mData[i]);
        if(i != tree.mData.size() - 1)
            os << ", ";
        else
            os << "}, ";
    }
    
    os << std::to_string(tree.Height()) << ", ";
    
    switch(tree.mBuildTraversal)
    {
        case BinaryTree::Traversal_PreOrder:
            os << "Pre"; break;
        case BinaryTree::Traversal_InOrder:
            os << "In"; break;    
        case BinaryTree::Traversal_PostOrder:
            os << "Post"; break;
    }
    os << "-Order}\n";
    return PrintNode(os, tree.GetRoot(), 0);
}