#pragma once
#include "Interfaces07.h"

class StringSort: public IStringSort{
    public:
    StringSort() {}
    ~StringSort() {}
    void sort(std::vector<std::string>& strings);
    void swap(std::vector<std::string>& a, int index1, int index2);
    void selectionSort(std::vector<std::string>& a);
};
