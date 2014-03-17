#pragma once

#include "Interfaces02.h"
#include "KeyValue.h"
#include<string>

class VectorKeyValue : public IVectorKeyValue{
    public:
    size_t length;
    size_t used;
    IKeyValue **items;

    int key;
    std::string value;

    VectorKeyValue(){
            length = 1;
            used = 0;
            items = new IKeyValue*[1];
    }
    ~VectorKeyValue(){}

    void push_back(IKeyValue *item);
    void pop_back();
    IKeyValue* get(int index);
    void set(int index, IKeyValue *item);
    size_t size();

};
