#include "LinkedListSort.h"
#include <iostream>
using namespace std;

LinkedListNode* LinkedListSort::sort(LinkedListNode* head){
    MergeSort(&head);
    return head;
}

void LinkedListSort::MergeSort(LinkedListNode **head_ref){
    LinkedListNode* head = *head_ref;
    LinkedListNode* split_a = NULL;
    LinkedListNode* split_b = NULL;
    LinkedListNode* one_way;
    LinkedListNode* two_way;
    if(head == NULL or head->next == NULL){
        return;
    }

    if(head == NULL or head->next == NULL){
        split_a = head;
        split_b = NULL;
    }
    else{
        one_way = head;
        two_way = head->next;
        while(two_way !=NULL){
            two_way = two_way->next;
            if(two_way !=NULL){
                one_way = one_way->next;
                two_way = two_way->next;
            }
        }

    split_a = head;
    split_b = one_way->next;
    one_way->next = NULL;

    MergeSort(&split_a);
    MergeSort(&split_b);
    *head_ref = Merge(split_a, split_b);
    
}
}

LinkedListNode* LinkedListSort::Merge(LinkedListNode *a, LinkedListNode* b){
    LinkedListNode* result = NULL;
    if(a == NULL)
        return b;
    else if(b == NULL)
        return a;
    if(a->key <= b->key){
        result = a;
        result->next = Merge(a->next,b);
    }
    else{
        result = b;
        result->next = Merge(a, b->next);
    }
    return result;

}

void LinkedListSort::print(LinkedListNode* head){
    LinkedListNode *start = head;
    cout << "\n";
    while(start!=NULL){
        cout <<"\t "<<start->key;
        start = start->next;
    }

    
}
