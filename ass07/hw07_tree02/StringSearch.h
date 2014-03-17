#pragma once
#include "Interfaces07.h"
#include <vector>
#include <string>

class StringSearch: public IStringSearch{
    
  public:
    std::string data;
  StringSearch(){
    }
  ~StringSearch(){
    }
  void prepareText(std::string text);
  std::vector<int> search(std::string pattern);
};
