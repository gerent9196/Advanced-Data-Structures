#include "StringSort.h"

void StringSort::sort(std::vector<std::string>& strings){

    selectionSort(strings);

}
void StringSort::swap(std::vector<std::string>& a, int index1, int index2){
  std::string lhs = a[index1];
  std::string rhs = a[index2];
  a[index1] = rhs;
  a[index2] = lhs;
}

void StringSort::selectionSort(std::vector<std::string>& a){
  size_t j, least;
  for(size_t i = 0; i < (a.size() - 1); ++i){
    for(j = i + 1, least = i; j < a.size(); ++j){
      if(a[j].compare(a[least]) < 0){
        least = j;
      }
    }
    swap(a, least, i);
  }
}
