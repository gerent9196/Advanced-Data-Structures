#pragma once

#include "Interfaces01.h"

class SingleNode : public ISingleNode{
    public:
        int value;
        ISingleNode* next;

        SingleNode(){}
        ~SingleNode() {}
        void setValue(int value);
        int getValue();
        ISingleNode* getNext();
        void setNext(ISingleNode *next);
};
