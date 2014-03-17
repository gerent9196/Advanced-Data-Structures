#pragma once

#include <vector>
#include <string>
#include <set>
#include <map>

#include "Interfaces05.h"

struct CommandsGraph {
  std::set<std::string> vertices;
  std::map<std::string, std::map<std::string, int> > edges;
};

class Commands05 {
public:
  void readReads(std::string filename, std::vector<std::string>& reads);
  void writeReads(std::string filename, std::vector<std::string>& reads);
  void readBuildGraphResults(std::string filename, CommandsGraph& results);
  void writeBuildGraphResults(std::string filename, IGraph * results);
  std::string readString(std::ifstream& fin);
  void writeString(std::ofstream& fout, std::string str);
};
