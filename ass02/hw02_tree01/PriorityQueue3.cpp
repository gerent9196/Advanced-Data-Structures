#include "PriorityQueue3.h"
#include<iostream>
#include <string>
#include "VectorString.h"

void PriorityQueue3::enqueue(IKeyValue * key_value){
    //cout << "\n insert pq1 key"<< key_value->getKey() << " " << key_value->getValue() << this;
    //cout << "\n bnode" << bnode->getDegree() << " " << bnode->getLeft() << " " << bnode->getRight() << " " << bnode->getParent();
    //cout <<"\n key "<< key_value->getKey() <<"value :" << key_value->getValue();
    if(this->first == 1){
        this->bl->add_to_binomial(key_value);
        this->first = 2;
        //cout << "printing inside scope adding:" << this->bl->getHeader().get(0);
        return;
        }
    BinomialList *bl2 = new BinomialList();
    bl2->add_to_binomial(key_value);
    this->bl->merge(bl2);
}

void PriorityQueue3::merge(IPriorityQueue * input_queue){
    //cout<< "\n Merge:";
    PriorityQueue3 *input_queue2 = static_cast<PriorityQueue3*> (input_queue);
    /*
    for(int i=0;i<input_queue2->bl->getHeader()->size(); i++){
        this->bl->getHeader()->push_back(input_queue2->bl->getHeader()->get(0));
    }
    this->bl->check_header();
    this->bl->print();
    */
    this->bl->merge(input_queue2->bl);
}

IVectorKeyValue* PriorityQueue3::returnSorted(){
}

int PriorityQueue3::lowestKey(){
    VectorBnode* head = bl->getHeader();
    int key = head->get(0)->getKeyValue()->getKey();
    for(int i = 0; i< head->size(); i++){
        if(key > head->get(i)->getKeyValue()->getKey())
            key = head->get(i)->getKeyValue()->getKey();
    }
    return key;
}

IVectorString* PriorityQueue3::lowestValues(){
    VectorBnode* head = bl->getHeader();
    int key = head->get(0)->getKeyValue()->getKey();
    string value = head->get(0)->getKeyValue()->getValue();
    for(int i = 0; i< head->size(); i++){
        if(key > head->get(i)->getKeyValue()->getKey()){
            key = head->get(i)->getKeyValue()->getKey();
            value = head->get(i)->getKeyValue()->getValue();
            //cout << "\nlowest key:" << key;
            //cout << "\nlowest value:" << value;
            }
    }
    IVectorString *vs = new VectorString();
    vs->push_back(value);
    return vs;
}

void PriorityQueue3::dequeue(){
    bl->delete_node();
}

size_t PriorityQueue3::size(){
    VectorBnode* head = bl->getHeader();
//    bl->print();
    int count= 0;
    for(int i = 0; i< head->size(); i++){
        Bnode *temp_node = head->get(i);
        count+=temp_node->getDegree();
    }
    //cout<<"\nsize is :"<< count;
    return count;
}


