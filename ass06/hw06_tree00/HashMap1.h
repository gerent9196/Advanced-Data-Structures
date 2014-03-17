#pragma once
#include "Interfaces06.h"
#include "Pair.h"
#include <vector>

class HashMap1 : public IHashMap{
  public:  
  std::vector<Pair *> hash;
  HashMap1() { 
}
  ~HashMap1() { }
  int binary_search(std::vector<Pair*>& hash, CompositeKey &key, int low, int end);
  int find_by_binary_search(std::vector<Pair*>& hash, CompositeKey &key);
  void insert(CompositeKey key, int value);
  void remove(CompositeKey key);
  bool containsKey(CompositeKey key);
  int getValue(CompositeKey key);
  int kthMinValue(int k);
  int size();
};
