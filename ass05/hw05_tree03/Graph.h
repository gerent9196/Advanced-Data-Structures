#pragma once

#include "Interfaces05.h"
#include <vector>

class Graph: public IGraph {
  std::vector<IVertex *> vertices;
    
  public:
  Graph() { }
  ~Graph() { }
  IVertex * insertVertex(std::string name) ;
  std::vector<IVertex *> getVertices() ;
};
