#include <vector>

class LinkedList
{
    public:
        struct Node
        {
            Node(int d) : data(d), pNext(nullptr) {};
            int data;
            Node* pNext;
        }; 
    
        LinkedList(std::vector<int> data) 
        {
            mpHead = new Node(data[0]);
            Node* pCurrent = mpHead;
            for(int i = 1; i < data.size(); ++i)
            {
                Node* pNew = new Node(data[i]);
                pCurrent->pNext = pNew; 
                pCurrent = pNew; 
            }
        }
    
        void Clear()
        {
            Node* pCurrent = mpHead;
            while(pCurrent != nullptr)
            {
                Node* deadNode = pCurrent;
                pCurrent = pCurrent->pNext;
                delete deadNode;
            }
        }
        
        Node* GetHead() { return mpHead; }
    
    private:
        Node* mpHead = nullptr;
};
