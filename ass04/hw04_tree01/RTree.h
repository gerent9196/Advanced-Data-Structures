#pragma once
#include "Interfaces04.h"

class RTree: public IRTree { 
  public:
  RTree() {}
  ~RTree() {}

  std::vector<IPoint *> RPoints;
  void hilbertSort(std::vector<IPoint *>& points) ;
  void bulkInsert(std::vector<IPoint *>& points) ;
  std::vector<IPoint *> findWithin(IPoint * top_left, IPoint * bottom_right) ;
  int log2(int);
  void insertionSort(long long inc,long long start, std::vector<IPoint *>& ,std::vector<long long>& dist);
  void shellSort(std::vector<IPoint *>& ,std::vector<long long>& dist);
};
