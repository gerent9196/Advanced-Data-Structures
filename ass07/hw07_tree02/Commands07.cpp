#include "Commands07.h"
#include <fstream>

std::string Commands07::readString(std::ifstream& fin)
{
  int size;
  fin.read((char *) &size, sizeof(int));
  char * ch = new char[size+1];
  fin.read((char *) ch, sizeof(char)*size);
  ch[size] = 0;
  std::string ret(ch);
  delete [] ch;
  return ret;
}

void Commands07::writeString(std::ofstream& fout, std::string str)
{
  int size = str.size();
  fout.write((char *) &size, sizeof(int));
  char * ch = new char[size];
  fout.write((char *) str.c_str(), sizeof(char)*size);
}

//http://stackoverflow.com/questions/2602013/read-whole-ascii-file-into-c-stdstring
std::string Commands07::readStringFile(std::string filename)
{
  std::ifstream fin(filename.c_str(), std::ios::in | std::ios::binary);
  if(fin.good() == false){
    return "";
  }

  std::string ret;  
  fin.seekg(0, std::ios::end);
  ret.resize(fin.tellg());
  fin.seekg(0, std::ios::beg);
  fin.read(&ret[0], ret.size());
  fin.close();
  return ret;
}

void Commands07::writeStringFile(std::string filename, std::string str)
{
  std::ofstream fout(filename.c_str(), std::ios::binary);
  if(fout.good() == false){
    return;
  }

  fout.write(&str[0], str.size());
  fout.close();
}

void Commands07::loadStringSearchCommmands(std::string filename, std::vector<StringSearchCmd>& cmds)
{
  std::ifstream fin(filename.c_str(), std::ios::binary);
  if(fin.good() == false){
    return;
  }

  long long len;
  fin.read((char *) &len, sizeof(long long));
  for(long long i = 0; i < len; ++i){
    StringSearchCmd curr;
    curr.to_find = readString(fin);
    long long vec_len;
    fin.read((char *) &vec_len, sizeof(long long));
    for(long long j = 0; j < vec_len; ++j){
      int index;
      fin.read((char *) &(index), sizeof(int));
      curr.positions.push_back(index);
    }
    cmds.push_back(curr);
  }
}

void Commands07::saveStringSearchCommmands(std::string filename, std::vector<StringSearchCmd>& cmds)
{
  std::ofstream fout(filename.c_str(), std::ios::binary);
  if(fout.good() == false){
    return;
  }

  long long len = cmds.size();
  fout.write((char *) &len, sizeof(long long));
  for(long long i = 0; i < len; ++i){
    StringSearchCmd curr = cmds[i];
    writeString(fout, curr.to_find);
    long long vec_len = curr.positions.size();
    fout.write((char *) &(vec_len), sizeof(long long));
    for(long long j = 0; j < vec_len; ++j){
      int index = curr.positions[j];
      fout.write((char *) &(index), sizeof(int));
    }
  }
  fout.flush();
  fout.close();
}

void Commands07::readReads(std::string filename, std::vector<std::string>& reads)
{
  std::ifstream fin(filename.c_str());
  if(fin.good() == false){
    return;
  }

  while(fin.eof() == false){
    char buffer[65535];
    fin.getline(buffer, 65535);
    std::string str = std::string(buffer);
    if(str != ""){
      reads.push_back(str);
    }
  }
  fin.close();
}

void Commands07::writeReads(std::string filename, std::vector<std::string>& reads)
{
  std::ofstream fout(filename.c_str());
  if(fout.good() == false){
    return;
  }

  for(size_t i = 0; i < reads.size(); ++i){
    fout << reads[i] << "\n";
  }
  fout.close();
}

void Commands07::loadSpellCheckCommands(std::string filename, std::vector<SpellCheckCmd>& cmds)
{
  std::ifstream fin(filename.c_str(), std::ios::binary);
  if(fin.good() == false){
    return;
  }

  long long len;
  fin.read((char *) &len, sizeof(long long));
  for(long long i = 0; i < len; ++i){
    SpellCheckCmd curr;
    curr.word = readString(fin);
    long long vec_len;
    fin.read((char *) &vec_len, sizeof(long long));
    for(long long j = 0; j < vec_len; ++j){
      std::string correction = readString(fin);
      curr.corrections.push_back(correction);
    }
    cmds.push_back(curr);
  }
}
  
void Commands07::saveSpellCheckCommands(std::string filename, std::vector<SpellCheckCmd>& cmds)
{
  std::ofstream fout(filename.c_str(), std::ios::binary);
  if(fout.good() == false){
    return;
  }

  long long len = cmds.size();
  fout.write((char *) &len, sizeof(long long));
  for(long long i = 0; i < len; ++i){
    SpellCheckCmd curr = cmds[i];
    writeString(fout, curr.word);
    long long vec_len = curr.corrections.size();
    fout.write((char *) &(vec_len), sizeof(long long));
    for(long long j = 0; j < vec_len; ++j){
      std::string correction = curr.corrections[j];
      writeString(fout, correction);
    }
  }
  fout.flush();
  fout.close();
}
