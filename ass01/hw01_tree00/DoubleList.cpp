#include "DoubleList.h"
#include <iostream>
using namespace std;

void DoubleList::setHead(IDoubleNode* head){
    this->head = head;
}

void DoubleList::setTail(IDoubleNode* tail){
    this->tail = tail;
}

void DoubleList::addSorted(int value){
   //first time
    if((this->head == NULL) and (this->tail == NULL)){

        IDoubleNode *new_node = new DoubleNode();
        new_node->setValue(value);
        new_node->setNext(NULL);
        new_node->setPrev(NULL);
        this->head = new_node;
        this->tail = new_node;
        count++;
        return;
    }
    //second time
    if (this->head == this->tail){
        //only one element there
        IDoubleNode* elem = new DoubleNode();
        elem->setValue(value);
        if(head->getValue() < value){
            //add next to head
            elem->setPrev(head);
            elem->setNext(NULL);

            head->setNext(elem);
            this->tail = elem;
        }
        else{
            //add prev to head

            elem->setNext(head);
            elem->setPrev(NULL);

            head->setPrev(elem);
            this->head = elem;
        }
        count++;
        return;
    }
    if ( value <= head->getValue()){
        IDoubleNode *temp = new DoubleNode();
        temp->setValue(value);
        
        temp->setNext(this->head);
        temp->setPrev(NULL);

        head->setPrev(temp);
        this->head = temp;
        count++;
        return;
    }
    if ( value >= tail->getValue()){
        IDoubleNode *temp = new DoubleNode();
        temp->setValue(value);
        
        temp->setNext(NULL);
        temp->setPrev(this->tail);

        tail->setNext(temp);
        this->tail = temp;
        count++;
        return;
    }

    
    IDoubleNode* add_after_this = this->find_where(this->head, this->tail, value, count);

    IDoubleNode* temp1 = new DoubleNode();
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

IDoubleNode* DoubleList::find_where(IDoubleNode *start, IDoubleNode* end, int value, int count){
    if( (value>=start->getValue() and (value<=end->getValue()) and (start->getNext() == end))){
        return start;
    }
    if( (value>start->getValue() and (value < end->getValue() ))){
        //between
        count = count/2;
        if(count ==0) 
            count=1;
        IDoubleNode* temp = start;
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

void DoubleList::rearrange(IDoubleNode*& start, int limit){
    if(start == NULL)
        return;
    //cout << "starting rearrange" << "\n" << start;
    IDoubleNode* rearrange_start;
    IDoubleNode* rearrange_end = NULL;
    if(start == NULL)
        return;
    
    for(int i=0;i<limit;i++){
        if(i==0){
            rearrange_start = start;
        }
        int k = i+1;
        //cout <<"\n start " << start->getValue() << " rearr start:" << rearrange_start->getValue(); 

        int flag=0;

        IDoubleNode* prev = start;
        IDoubleNode* p = start->getNext();
        IDoubleNode* temp = start->getNext();
        start->setNext(start->getPrev());
        start->setPrev(temp);

        start = p;
        if(p==NULL)
            flag = 1;
        
        if(k == limit || flag == 1){
           
            //cout << "\n shuffling start with end";
            k = 0;
            rearrange_end = prev;
            if (rearrange_end == NULL){
                start = NULL;
                return;
            }
            //cout << "\n rearrange_end " << rearrange_end->getValue() ;
            IDoubleNode* t;
            t = rearrange_end->getPrev();
            rearrange_end->setPrev(rearrange_start->getNext());
            rearrange_start->setNext(t);

            //rearrange_start->getNext()->setNext(rearrange_start);
            
            if (rearrange_start->getNext() != NULL)
                rearrange_start->getNext()->setPrev(rearrange_start);
            if (rearrange_end->getPrev() != NULL)
                rearrange_end->getPrev()->setNext(rearrange_end);
            if (rearrange_end->getPrev() == NULL)
                this->head = rearrange_end;
            if (rearrange_start -> getNext() == NULL)
                this->tail = rearrange_start;
            return;
        }
    }

    
    
    /*
    cout << "rearranging:";
    if(start->getNext() == NULL){
        start->setNext(start->getPrev());
        start->setPrev(NULL);
        this->head = start;
    }
    for(int i=0;i<limit;i++){
        if(start->getPrev() == NULL)
            this->tail = start;
        IDoubleNode *t = start->getNext();
        start->setNext(start->getPrev());
        start->setPrev(t);
        start = t;
        rearrange(start, limit);
        }
*/
}
IDoubleNode* DoubleList::getHead(){
    return this->head;
}

IDoubleNode* DoubleList::getTail(){
    return this->tail;
}

void DoubleList::printlist(){
    IDoubleNode* start = this->head;
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

void DoubleList::orderSort2(){
    IDoubleNode* start = this->head;
    //this->printlist();
    for(int i=2; ; ){
        this->rearrange(start, i);
        if(start == NULL)
        break;
    }
    //cout << "After rearranging \n";
    //this->printlist();
}

void DoubleList::orderSort3(){
    IDoubleNode* start = this->head;
    //this->printlist();
    for(int i=3; ; ){
        this->rearrange(start, i);
        if(start == NULL)
        break;
    }
    //cout << "After rearranging \n";
    //this->printlist();
    //this->printlist();
}
void DoubleList::sequenceOrderSort(){
    IDoubleNode* start = this->head;
    //this->printlist();
    for(int i=2; ; i++ ){
        this->rearrange(start, i);
        if(start == NULL)
        break;
    }
    //cout << "After rearranging \n";
    //this->printlist();
    //this->printlist();
    //this->printlist();
}
void DoubleList::reverse(){
    IDoubleNode* start = this->head;
    for(int i=this->count; ;  ){
        this->rearrange(start, i);
        if(start == NULL)
        break;
    }
    //cout << "After rearranging \n";
}
