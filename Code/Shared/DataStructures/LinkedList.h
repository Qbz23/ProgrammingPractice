#pragma once

#include <vector>
#include <iostream>

class LinkedList
{
    public:
        struct Node
        {
            Node(int d) : data(d), pNext(nullptr) {};
            int data;
            Node* pNext;
        }; 
    
        LinkedList() {}
    
        LinkedList(std::vector<int> data) ;
        ~LinkedList();
        LinkedList(const LinkedList& l);
        LinkedList& operator=(const LinkedList& l);
        
        void Push(int d);
                
        inline Node* GetHead() { return mpHead; }
        inline const Node* GetHead() const { return mpHead; }
        
        bool operator==(const LinkedList other) const;
        inline bool operator!=(const LinkedList other) const { return !(*this == other); }
    
    private:
        Node* mpHead = nullptr;
        
        void CopyImpl(const LinkedList& l);      

};

std::ostream& operator<<(std::ostream& os, LinkedList ll);
