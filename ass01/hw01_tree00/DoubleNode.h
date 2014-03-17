#pragma once

#include "Interfaces01.h"
#include "SingleNode.h"

class DoubleNode : public IDoubleNode{
    public:
        int value;
        IDoubleNode* next;
        IDoubleNode* prev;

        DoubleNode(){}
        ~DoubleNode(){}
        void setValue(int value);
        int getValue();
        IDoubleNode* getPrev();
        IDoubleNode* getNext();
        void setPrev(IDoubleNode* prev);
        void setNext(IDoubleNode* next);
};
