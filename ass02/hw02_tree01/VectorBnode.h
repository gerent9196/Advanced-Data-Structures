#pragma once

#include "Interfaces02.h"
#include "Bnode.h"
#include<string>

class VectorBnode{
    public:
    size_t length;
    size_t used;
    Bnode **items;

    int key;
    std::string value;

    VectorBnode(){
            length = 1;
            used = 0;
            items = new Bnode*[1];
    }
    ~VectorBnode(){}

    void push_back(Bnode *item);
    void pop_back();
    Bnode* get(int index);
    void set(int index, Bnode *item);
    size_t size();

};
