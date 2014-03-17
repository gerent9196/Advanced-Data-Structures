#pragma once
#include "Interfaces06.h"
#include "Pair.h"

class BulkHashMap: public IBulkHashMap{
    public:
    std::vector<Pair *> hash[300];
    BulkHashMap() { }
    ~BulkHashMap() { } 
    int hash_code(CompositeKey key);
    void insert(std::vector<std::pair<CompositeKey, int> >& data) ;
    int getValue(CompositeKey key) ;
};
