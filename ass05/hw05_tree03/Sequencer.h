#pragma once

#include "Interfaces05.h"


class Sequencer: public ISequencer {
  public:
  Sequencer() { }
  virtual ~Sequencer() { }
  IGraph * buildGraph(std::vector<std::string>& reads) ;
  std::vector<std::string> tsp(std::string start_read, IGraph * graph) ;
  std::string assemble(std::vector<std::string>& tsp_result);
  int calculate_other_bound(std::vector<IVertex* >& path, IGraph * graph);
};
