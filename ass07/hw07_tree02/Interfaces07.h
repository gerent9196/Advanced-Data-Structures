#pragma once

#include <string>
#include <vector>

struct IStringSearch {
  IStringSearch() {}
  virtual ~IStringSearch() {}
  virtual void prepareText(std::string text) = 0;
  virtual std::vector<int> search(std::string pattern) = 0;
};

struct IStringSort {
  IStringSort() {}
  virtual ~IStringSort() {}
  virtual void sort(std::vector<std::string>& strings) = 0;
};

//suggestCorrections returns the words from the dictionary that have exactly
//one character difference. this could be from insertion, removal or substituion
struct ISpellCheck {
  ISpellCheck() {}
  virtual ~ISpellCheck() {}
  virtual void loadDictionary(std::vector<std::string>& words) = 0;
  virtual std::vector<std::string> suggestCorrections(std::string word) = 0;
};

struct ICompress {
  ICompress() {}
  virtual ~ICompress() {}
  virtual std::string compress(std::string input) = 0;
  virtual std::string decompress(std::string compressed) = 0;
};
