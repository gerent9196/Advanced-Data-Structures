#pragma once

#include "Interfaces02.h"
#include <string>
#include "BinomialList.h"

class PriorityQueue3: public IPriorityQueue{
    public:
    BinomialList* bl;
    int first;
    PriorityQueue3(){
        first = 1;
        this->bl = new BinomialList();
    }
    ~PriorityQueue3(){
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
