#pragma once

#include "Interfaces02.h"
#include <string>
#include "vector.h"
#include <iostream>
using namespace std;

class node{
    public:
    vector <string> *words;
    int key;
    ~node(){
    }
    node(){
    words = new vector<string>;
    }
    node(const node& p){
        key = p.key;
        words = p.words;
    }
};
class PriorityQueue2: public IPriorityQueue{
    //DoubleList *l;
    //vector *<int, vector<string>> list;
    IVectorString * lowest_value;
    //vector <node*>  *nodes ;
    vector<IKeyValue*> *nodes;
    int count;

    public:
    PriorityQueue2(){
         //list = new vector
         nodes = new vector <node*>;
         count = 0;
         lowest_value = NULL;
         IKeyValue *dummy_node = new KeyValue();
         nodes->push_back(dummy_node);
         std::cout << "node size"<< nodes->size();
    }
    ~PriorityQueue2(){
    }
    void heapify(int i);
    bool recursive_insert(IKeyValue *, int); 
    void enqueue(IKeyValue * key_value) ;
    void merge(IPriorityQueue * input_queue) ;
    IVectorKeyValue * returnSorted() ;
    int lowestKey() ;
    IVectorString * lowestValues() ;
    void dequeue() ;
    size_t size() ;
    int left(int i);
    int right(int i);
    int parent(int i);
};
