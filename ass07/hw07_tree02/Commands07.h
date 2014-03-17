#pragma once

#include <vector>
#include <string>
#include <set>
#include <map>
#include "Interfaces07.h"

struct StringSearchCmd {
  std::string to_find;
  std::vector<int> positions;
};

struct SpellCheckCmd {
  std::string word;
  std::vector<std::string> corrections;
};

class Commands07 {
public:
  std::string readString(std::ifstream& fin);
  void writeString(std::ofstream& fout, std::string str);
  
  std::string readStringFile(std::string filename);
  void writeStringFile(std::string filename, std::string str);

  void loadStringSearchCommmands(std::string filename, std::vector<StringSearchCmd>& cmds);
  void saveStringSearchCommmands(std::string filename, std::vector<StringSearchCmd>& cmds);

  void readReads(std::string filename, std::vector<std::string>& reads);
  void writeReads(std::string filename, std::vector<std::string>& reads);

  void loadSpellCheckCommands(std::string filename, std::vector<SpellCheckCmd>& cmds);
  void saveSpellCheckCommands(std::string filename, std::vector<SpellCheckCmd>& cmds);
};
