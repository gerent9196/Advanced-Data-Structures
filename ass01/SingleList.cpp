#include "SingleList.h"
#include <iostream>
using namespace std;

ISingleNode* SingleList::getHead(){
    return this->head;
}

void SingleList::setHead(ISingleNode* head){
    this->head = head;
}

void SingleList::addHead(int value){
    ISingleNode *node = new SingleNode();
    node->setValue(value);
    if(this->head == NULL)
        node->setNext(NULL);
    else
        node->setNext(this->head);
    this->setHead(node);
}

ISingleNode* SingleList::delete_node(ISingleNode *prev, ISingleNode* del_this){
    if(del_this == this->head and prev == NULL){
        ISingleNode* temp = head;
        this->setHead(head->getNext());
        return temp; 
    }
    if(del_this->getNext() == NULL){
        prev->setNext(NULL);
        return del_this; 
    }

    prev->setNext(del_this->getNext());
    return del_this;
}

void SingleList::insert_node(ISingleNode *prev, ISingleNode* ins_this, int head_ins = 0){
    if (prev == this->head and head_ins == 1 ){
        ins_this->setNext(this->head);
        this->head = ins_this;
    }
    else if(prev == NULL){
        ins_this->setNext(this->head);
        this->setHead(ins_this); 
    }
    else if(prev->getNext() == NULL){
        ins_this->setNext(prev->getNext());
        prev->setNext(ins_this);
    }
    else{
        ins_this->setNext(prev->getNext());
        prev->setNext(ins_this);
    }
}

void SingleList::printlist(){
    ISingleNode *start = this->head;
    while(start!=NULL){
        cout << "\nPrinting list item "<< start->getValue() << "\t" ;
        start = start->getNext();
    }
    cout <<"End \n";
}

void SingleList::orderSort2(){
    ISingleNode* base = this->head;
    ISingleNode* new_base = base;
    ISingleNode* prev = NULL;
    this->printlist();

    for(int i=2; ; ){
        this->rearrange(i, prev, new_base);
        if(new_base == NULL)
            break;
    }
    this->printlist();
}

void SingleList::orderSort3(){
    ISingleNode* base = this->head;
    ISingleNode* new_base = base;
    ISingleNode* prev = NULL;

    for(int i=3; ; ){
        this->rearrange(i, prev, new_base);
        if(new_base == NULL)
            break;
    }
    }

void SingleList::sequenceOrderSort(){
    ISingleNode* base = this->head;
    ISingleNode* new_base = base;
    ISingleNode* prev = NULL;

    for(int i=2; ; i++){
        this->rearrange(i, prev, new_base);
        if(new_base == NULL)
            break;
    }
}

void SingleList::rearrange(int i, ISingleNode*& prev, ISingleNode*& base){
    if(base == NULL)
        return;
    ISingleNode *saved_base = base;
    ISingleNode *end = base;
    ISingleNode *new_prev = NULL;
    int j = i -1;
    while( end!=NULL && j!=0){
        end = end->getNext();
        j--;
    }
    new_prev = end;
    ISingleNode *final_base ;
    if(end == NULL)
        final_base = end;
    else
        final_base = end->getNext();
        
    ISingleNode *new_base = end;
    ISingleNode *deleted_node;
    ISingleNode *to_del = base;
    j = i-1;
    while(j!=0){
        new_base = base->getNext();
        deleted_node = this->delete_node(prev, base);
        this->insert_node(end, deleted_node);
        //end = end->getNext();
        base = new_base;
        j--; 
    }
    base = final_base;
    prev = saved_base;
}
void SingleList::reverse(){
    ISingleNode* base = this->head;
    ISingleNode* new_base = base;
    ISingleNode* prev = NULL;

    int i=0;
    ISingleNode* len_node = this->head;
    while(len_node !=NULL){
        i++;
        len_node = len_node->getNext();
        }
    for( i; ; ){
        this->rearrange(i, prev, new_base);
        if(new_base == NULL)
            break;
    }
}
