#include "LinkedListSort.h"
#include <iostream>
using namespace std;

LinkedListNode* LinkedListSort::sort(LinkedListNode* head){
   // cout << "start";
    //print(head);
    MergeSort(head);
    //cout << "end";
    //print(head);
    return head;
}

void LinkedListSort::MergeSort(LinkedListNode *head_ref){
    LinkedListNode* head = head_ref;
    LinkedListNode* split_a = NULL;
    LinkedListNode* split_b = NULL;
    LinkedListNode* one_way;
    LinkedListNode* two_way;
    split_a = head;
    if(head == NULL or head->next == NULL){
        return;
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

    split_b = one_way->next;
    one_way->next = NULL;
    }
    /*
    cout <<"\n split a:";
    print(split_a);
    cout <<"\n split b:";
    print(split_b);
    */
    MergeSort(split_a);
    MergeSort(split_b);
    head_ref = Merge(split_a, split_b);
}

LinkedListNode* LinkedListSort::Merge(LinkedListNode *p, LinkedListNode *q){
/*
    cout << "\n Merging:";
    print(p);
    cout << "\nList2";
    print(q);
    */
    LinkedListNode*  merged = NULL;
    LinkedListNode* temp = NULL;
    LinkedListNode* x = NULL;
    while(p!= NULL and q!=NULL){
        if (p->key < q->key){
            temp = p;
            p = p->next;
        }
        else{
            temp = q;
            q = q->next;
        }
        if(merged == NULL){
            merged = temp;
            x = temp;
        }
        else{
            merged->next = temp;
            merged = merged->next;
        }
    }
    if( p!= NULL){
        merged->next= p;
    }
    if(q!= NULL){
        merged->next = q;
    }
    /*
    cout << "\n output merged";
    print(x);
    */
    return x;

}

void LinkedListSort::print(LinkedListNode* head){
    LinkedListNode *start = head;
    cout << "\n";
    while(start!=NULL){
        cout <<"\t "<<start->key;
        start = start->next;
    }
}
