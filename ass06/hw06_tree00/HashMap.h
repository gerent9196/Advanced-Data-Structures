#pragma once
#include "Interfaces06.h"
#include "Pair.h"
#include <vector>

class HashMap : public IHashMap{
  public:  
  std::vector<Pair *> hash[400];
  HashMap() { 
}
  ~HashMap() { }
  void insert(CompositeKey key, int value);
  void remove(CompositeKey key);
  bool containsKey(CompositeKey key);
  int getValue(CompositeKey key);
  int kthMinValue(int k);
  int size();
  int hash_code(CompositeKey&);
};
