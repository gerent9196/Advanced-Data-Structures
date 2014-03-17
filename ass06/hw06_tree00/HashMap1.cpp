#include "HashMap1.h"
#include <iostream>
using namespace std;

void HashMap1::insert(CompositeKey key, int value){

    Pair* new_data = new Pair();
    new_data->key  = key;
    new_data->value = value;
    if(hash.size() == 0){
        hash.push_back(new_data);
        return;
    }
    int to_insert = binary_search(hash, key, 0, hash.size());
    if( key < hash[to_insert]->key){
        hash.insert( hash.begin() + to_insert, new_data);
       } 
    else{
        hash.insert( hash.begin() + to_insert+1, new_data);
    }
}

int HashMap1::binary_search(std::vector<Pair*>& hash, CompositeKey & key, int low, int end){
       
    int mid = (low+end)/2;
    if(low == mid)
        return low;
    if(end == mid)
        return mid;
    if(  hash[mid]->key < key){
        binary_search(hash, key, mid ,end); 
        }
    else {
        binary_search(hash, key, low ,mid); 
    }
}

int HashMap1::find_by_binary_search(std::vector<Pair*>& hash, CompositeKey& key){
  int low = 0;
  int mid;
  int high = hash.size()-1;

  while(low <= high){
    mid = (low + high) / 2;
    if(key < hash[mid]->key){
      high = mid - 1;
    } else if(hash[mid]->key < key){
      low = mid + 1;
    } else {
      return mid;
    }
  }
  return -1;
}
void HashMap1::remove(CompositeKey key){
    int index = find_by_binary_search(hash, key);
    if(index != -1)
        hash.erase( hash.begin() + index);
}
bool HashMap1::containsKey(CompositeKey key){
    int index = find_by_binary_search(hash, key);
    if(index != -1){
            return true;
        }
return false;
}
int HashMap1::getValue(CompositeKey key){
    int index = find_by_binary_search(hash, key);
    if(index != -1){
            return hash[index]->value;
        }
}
int HashMap1::kthMinValue(int k){
    return hash[k]->value;
}
int HashMap1::size(){
    return hash.size();
}
