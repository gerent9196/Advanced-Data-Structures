#pragma once

#include "Interfaces02.h"
#include <string>
#include "FibonacciList.h"

class PriorityQueue4: public IPriorityQueue{
    public:
    FibonacciList* bl;
    int first;
    PriorityQueue4(){
        first = 1;
        this->bl = new FibonacciList();
    }
    ~PriorityQueue4(){
        delete bl;
    }




void enqueue(IKeyValue * key_value) ;
void merge(IPriorityQueue * input_queue) ;
IVectorKeyValue * returnSorted() ;
int lowestKey() ;
IVectorString * lowestValues() ;
void dequeue() ;
size_t size() ;


};
