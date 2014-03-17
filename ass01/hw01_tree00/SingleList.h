#pragma once

#include "Interfaces01.h"
#include "SingleNode.h"

class SingleList : public ISingleList{
    public:
        ISingleNode* head;
        int count;
        SingleList() 
        {
        head = NULL;
        count=0;
        }
        ~SingleList() {}
        ISingleNode *getHead();
        ISingleNode *delete_node(ISingleNode* prev, ISingleNode* del_this);
        void insert_node(ISingleNode* prev, ISingleNode* ins_this, int head_ins);
        void rearrange(int i, ISingleNode*& prev, ISingleNode*& base);
        void setHead(ISingleNode *head);
        void addHead(int value);
        void orderSort2();
        void orderSort3();
        void sequenceOrderSort();
        void reverse();
        void printlist();
};
