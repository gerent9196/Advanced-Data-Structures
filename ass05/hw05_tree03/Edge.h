#pragma once

#include "Interfaces05.h"
#include <vector>

class Edge: public IEdge {
  IVertex *target;
  int weight;
  public:
  Edge() { }
  ~Edge() { }
  IVertex * getTarget() ;
  void setTarget(IVertex * target) ;
  int getWeight() ;
  void setWeight(int value) ;
};
