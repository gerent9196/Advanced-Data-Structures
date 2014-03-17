#include "DoubleNode.h"
#include <iostream>
using namespace std;
class DoubleList {
    public:
        
        DoubleNode *head;
        DoubleNode *tail;
        int count;

        DoubleList(){
            count = 0;
            head = NULL;
            tail = NULL;
        }
        ~DoubleList(){
        }

        DoubleNode* find_where(DoubleNode* start, DoubleNode* end, int value, int count);
        void setHead(DoubleNode* head);
        void setTail(DoubleNode* tail);
        void addSorted(int value);
        DoubleNode* getHead();
        DoubleNode* getTail();
        void printlist();

};



