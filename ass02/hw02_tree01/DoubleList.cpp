#include "DoubleList.h"
#include <iostream>
using namespace std;

void DoubleList::setHead(DoubleNode* head){
    this->head = head;
}

void DoubleList::setTail(DoubleNode* tail){
    this->tail = tail;
}

void DoubleList::delete_root(){
    if(this->head->getNext()!= NULL){
        this->head = this->head->getNext();
        count--;
        }
}
void DoubleList::eg(){
        DoubleNode* new_node = new DoubleNode();
        }

void DoubleList::addSorted(int value, std::string word){
   //first time 
    if((this->head == NULL) and (this->tail == NULL)){

        DoubleNode* new_node = new DoubleNode();
        new_node->setValue(value);
        new_node->setNext(NULL);
        new_node->setPrev(NULL);
        new_node->setWords(word);
        this->head = new_node;
        this->tail = new_node;
        count++;
        return;
    }
    //second time
    if (this->head == this->tail){
        //only one element there
        DoubleNode* elem = new DoubleNode();
        elem->setValue(value);
        if(head->getValue() == value){
            head->setWords(word);
            return;
        }
        if(head->getValue() < value){
            //add next to head
            elem->setPrev(head);
            elem->setNext(NULL);
            elem->setWords(word);
            head->setNext(elem);
            this->tail = elem;
        }
        else if (head->getValue()>value) {
            //add prev to head

            elem->setNext(head);
            elem->setPrev(NULL);
            elem->setWords(word);

            head->setPrev(elem);
            this->head = elem;
        }
        count++;
        return;
    }
    if ( value < head->getValue()){
        DoubleNode *temp = new DoubleNode();
        temp->setValue(value);
        
        temp->setNext(this->head);
        temp->setPrev(NULL);
        temp->setWords(word);

        head->setPrev(temp);
        this->head = temp;
        count++;
        return;
    }
    if ( value > tail->getValue()){
        DoubleNode *temp = new DoubleNode();
        temp->setValue(value);
        temp->setWords(word);
        
        temp->setNext(NULL);
        temp->setPrev(this->tail);

        tail->setNext(temp);
        this->tail = temp;
        count++;
        return;
    }

    
    DoubleNode* add_after_this = this->find_where(this->head, this->tail, value, count);
    if(add_after_this->getValue() == value){
        add_after_this->setWords(word);
    //    count++;
        return;
    }
        
    DoubleNode* temp1 = new DoubleNode();
    temp1->setWords(word);
    temp1->setValue(value);
    temp1->setNext(add_after_this->getNext());
    temp1->setPrev(add_after_this);
    add_after_this->setNext(temp1);
    temp1->getNext()->setPrev(temp1);
    if(temp1->getNext() == NULL)
        this->tail = temp1;
    count++;
    //this->printlist(); 
}
DoubleNode* DoubleList::find_where(DoubleNode *start, DoubleNode* end, int value, int count){
    if( (value>start->getValue() and (value<end->getValue()) and (start->getNext() == end))){
        return start;
    }
    if( (value>start->getValue() and (value < end->getValue() ))){
        //between
        count = count/2;
        if(count ==0) 
            count=1;
        DoubleNode* temp = start;
        for(int i=0;i<count;i++)
            temp = temp->getNext();
        if (value > temp->getValue())
            start = temp;
        else
            end = temp;
        return find_where(start, end, value, count);
        }
    if (value <= start->getValue() )
        return start;
    if (value >= end->getValue())
        return end;
}
DoubleNode* DoubleList::getHead(){
    return this->head;
}

DoubleNode* DoubleList::getTail(){
    return this->tail;
}

void DoubleList::printlist(){
    DoubleNode* start = this->head;
    std::cout<<"start"<<"\n";
    while(start != NULL){
        std::cout << "printing list "<< start->getValue() << "\n";
        start = start->getNext();
    }
    std::cout<<"end"<<" count is "<<this->count<< "\n";

    start = this->tail;
    std::cout<<"tail"<<"\n";
    while(start != NULL){
        std::cout << "printing list "<< start->getValue() << "\n";
        start = start->getPrev();
    }
    std::cout<<"end"<<" count is "<<this->count<< "\n";
    
}

