#include "BulkHashMap.h"
#include <iostream>
using namespace std;

void BulkHashMap::insert(std::vector<std::pair<CompositeKey, int> >& data) {

    for(int i=0; i< data.size(); i++){
        int hash_value = hash_code(data[i].first);
        Pair* new_data = new Pair();
        new_data->key = data[i].first;
        new_data->value = data[i].second;
        hash[hash_value].push_back(new_data);
    }
   } 
int BulkHashMap::getValue(CompositeKey key) {
    int hash_value = hash_code(key);
    std::vector<Pair *> bucket = hash[hash_value]; 
    for(int i=0; i< bucket.size(); i++){
        if(bucket[i]->key == key)
            return bucket[i]->value;
    }
}

int BulkHashMap::hash_code(CompositeKey key){
    return ((key.key1+ int(key.key2*100) + key.key3) % 150);
}
