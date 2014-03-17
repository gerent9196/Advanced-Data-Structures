#pragma once
#include "Interfaces03.h"


class LinkedListSort: public ILinkedListSort{
    public:
    LinkedListSort(){
    }
    ~LinkedListSort(){
    }
    LinkedListNode* sort(LinkedListNode * list);
    void MergeSort(LinkedListNode **head);
    LinkedListNode* Merge(LinkedListNode *a, LinkedListNode* b);
    void print(LinkedListNode* head);
};
