#pragma once

#include "Interfaces01.h"
#include "DoubleNode.h"

class DoubleList : public IDoubleList{
    public:
        
        IDoubleNode *head;
        IDoubleNode *tail;
        int count;

        DoubleList(){
            count = 0;
            head = NULL;
            tail = NULL;
        }
        ~DoubleList(){
        }

        IDoubleNode* find_where(IDoubleNode* start, IDoubleNode* end, int value, int count);
        void rearrange(IDoubleNode*& start ,int i);
        void setHead(IDoubleNode* head);
        void setTail(IDoubleNode* tail);
        void addSorted(int value);
        IDoubleNode* getHead();
        IDoubleNode* getTail();
        void printlist();
        void orderSort2();
        void orderSort3();
        void sequenceOrderSort();
        void reverse();

};



