#include "HashMap.h"
#include <iostream>
using namespace std;

void HashMap::insert(CompositeKey key, int value){
        int hash_value = hash_code(key);
        Pair* new_data = new Pair();
        new_data->key = key;
        new_data->value = value;
        hash[hash_value].push_back(new_data);
}
void HashMap::remove(CompositeKey key){
    int hash_value = hash_code(key);
    std::vector<Pair *> bucket = hash[hash_value]; 
    for(int i=0; i< bucket.size(); i++){
        if(bucket[i]->key == key)
            bucket.erase( bucket.begin() + i);
    }
    hash[hash_value] = bucket;
}
bool HashMap::containsKey(CompositeKey key){
    int hash_value = hash_code(key);
    std::vector<Pair *> bucket = hash[hash_value]; 
    if(bucket.size() == 0)
        return false;
    for(int i=0; i< bucket.size(); i++){
        if(bucket[i]->key == key)
            return true;
    }
    return false;
}
int HashMap::getValue(CompositeKey key){
    int hash_value = hash_code(key);
    std::vector<Pair *> bucket = hash[hash_value]; 
    for(int i=0; i< bucket.size(); i++){
        if(bucket[i]->key == key)
            return bucket[i]->value;
    }
}
int HashMap::kthMinValue(int k){
}
int HashMap::size(){
}
int HashMap::hash_code(CompositeKey &key){
    return ((key.key1+ int(key.key2*100) + key.key3) % 150);
}
