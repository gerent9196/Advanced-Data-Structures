#pragma once

#include "Interfaces02.h"
#include <string>
#include "DoubleList.h"

class PriorityQueue1: public IPriorityQueue{
    DoubleList *l;

    public:
    PriorityQueue1(){
         this->l = new DoubleList();
    }
    ~PriorityQueue1(){
    }

    void enqueue(IKeyValue * key_value) ;
    void merge(IPriorityQueue * input_queue) ;
    IVectorKeyValue * returnSorted() ;
    int lowestKey() ;
    IVectorString * lowestValues() ;
    void dequeue() ;
    size_t size() ;
};
