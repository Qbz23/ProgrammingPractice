#include "BinaryTree.h"

#include <iostream>
#include <vector>
#include <cassert>
#include <string>

BinaryTree::BinaryTree(std::vector<int> initData, int maxDepth, Traversal t /* = Traversal_PreOrder */) : 
    mBuildTraversal(t)
{
    uint32_t dataIndex = 0;
    uint32_t unassignedParents = 0;
    mpRoot = BuildTree(initData, dataIndex, 0, maxDepth, unassignedParents);
    assert(dataIndex == initData.size());
    //Just for debug printing
    mData = initData;
}

BinaryTree::~BinaryTree()
{
    FreeTree(mpRoot);
}

BinaryTree::BinaryTree(const BinaryTree& bt) : mBuildTraversal(Traversal_PreOrder)
{
    CopyTree(bt);
}

BinaryTree& BinaryTree::operator=(const BinaryTree& bt)
{
    CopyTree(bt);
    return *this;
}

int BinaryTree::Height() const
{
    Node* pCur = mpRoot;
    int height = 0;
    //This assumes left will be longest which is safe w how this tree is built but not in general
    while (pCur != nullptr)
    {
        ++height;
        pCur = pCur->pLeft;
    }

    return height;
}

BinaryTree::Node* BinaryTree::BuildTree(std::vector<int> data, uint32_t& dataIndex,
    int curDepth, int maxDepth, uint32_t& unassignedParents)
{
    if (curDepth == maxDepth || (dataIndex + unassignedParents == data.size()))
    {
        return nullptr;
    }
    else
    {
        Node* pNew = nullptr;
        Node* pLeft = nullptr;
        Node* pRight = nullptr;
        int nextDepth = ++curDepth;
        switch (mBuildTraversal)
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

void BinaryTree::CopyTree(const BinaryTree& bt)
{
    mpRoot = CopyTreeImpl(bt.GetRoot());
    mData = bt.mData;
}

BinaryTree::Node* BinaryTree::CopyTreeImpl(const Node* pOther)
{
    Node* pNew = new Node(pOther->data);
    if (pOther->pLeft)
    {
        pNew->pLeft = CopyTreeImpl(pOther->pLeft);
    }
    if (pOther->pRight)
    {
        pNew->pRight = CopyTreeImpl(pOther->pRight);
    }

    return pNew;
}

//Does post order delete 
void BinaryTree::FreeTree(Node* pNode)
{
    if (pNode)
    {
        FreeTree(pNode->pLeft);
        FreeTree(pNode->pRight);
        delete pNode;
    }
}

static std::ostream& PrintNode(std::ostream& os, const BinaryTree::Node* pNode, uint32_t spaceCount)
{
    uint32_t kSpaceCountOffset = 4;
    if (pNode)
    {
        spaceCount += kSpaceCountOffset;

        //Right first b/c its on top
        PrintNode(os, pNode->pRight, spaceCount);

        //Self 
        os << std::endl;
        //Aplpy indent 
        for (uint32_t i = 0; i < spaceCount; ++i)
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
    for (uint32_t i = 0; i < tree.mData.size(); ++i)
    {
        os << std::to_string(tree.mData[i]);
        if (i != tree.mData.size() - 1)
            os << ", ";
        else
            os << "}, ";
    }

    os << std::to_string(tree.Height()) << ", ";

    switch (tree.mBuildTraversal)
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