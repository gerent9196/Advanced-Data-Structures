#include "PriorityQueue4.h"
#include<iostream>
#include <string>
#include "VectorString.h"

void PriorityQueue4::enqueue(IKeyValue * key_value){
    bl->add_to_fibonacci(key_value);
}

void PriorityQueue4::merge(IPriorityQueue * input_queue){
    PriorityQueue4 *input_queue2 = static_cast<PriorityQueue4*> (input_queue);
    /*
    for(int i=0;i<input_queue2->bl->getHeader()->size(); i++){
        this->bl->getHeader()->push_back(input_queue2->bl->getHeader()->get(0));
    }
    this->bl->check_header();
    this->bl->print();
    */
    this->bl->merge(input_queue2->bl);
}

IVectorKeyValue* PriorityQueue4::returnSorted(){
}

int PriorityQueue4::lowestKey(){
    return this->bl->lowest_val->getKeyValue()->getKey();
}

IVectorString* PriorityQueue4::lowestValues(){
    IVectorString *vs = new VectorString();
    vs->push_back(this->bl->lowest_val->getKeyValue()->getValue());
    return vs;
}

void PriorityQueue4::dequeue(){
    bl->delete_node();
}

size_t PriorityQueue4::size(){
    VectorBnode* head = bl->getHeader();
    int count= 0;
    for(int i = 0; i< head->size(); i++){
        Bnode *temp_node = head->get(i);
        count+=temp_node->getDegree();
    }
    //cout<<"\nsize is :"<< count;
    return count;
}


