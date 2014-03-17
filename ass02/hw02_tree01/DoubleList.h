#pragma once

#include "DoubleNode.h"
#include <iostream>
#include "VectorString.h"
using namespace std;
class DoubleList {
    public:
        
        DoubleNode *head;
        DoubleNode *tail;
        int count;

        void eg();

        DoubleList(){
            count = 0;
            head = NULL;
            tail = NULL;
        }
        ~DoubleList(){
        }

        DoubleNode* find_where(DoubleNode* start, DoubleNode* end, int value, int count);
        void setHead(DoubleNode* head);
        void delete_root();
        void setTail(DoubleNode* tail);
        void addSorted(int value, std::string word);
        DoubleNode* getHead();
        DoubleNode* getTail();
        void printlist();

};



