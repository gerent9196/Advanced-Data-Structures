#include "Commands05.h"
#include <fstream>

void Commands05::readReads(std::string filename, std::vector<std::string>& reads)
{
  std::ifstream fin(filename.c_str());
  if(fin.good() == false){
    return;
  }

  while(fin.eof() == false){
    char buffer[255];
    fin.getline(buffer, 255);
    std::string str = std::string(buffer);
    if(str != ""){
      reads.push_back(str);
    }
  }
  fin.close();
}

void Commands05::writeReads(std::string filename, std::vector<std::string>& reads)
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

std::string Commands05::readString(std::ifstream& fin)
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

void Commands05::readBuildGraphResults(std::string filename, CommandsGraph& results)
{
  std::ifstream fin(filename.c_str(), std::ios::binary);
  if(fin.good() == false){
    return;
  }

  long long size;
  fin.read((char *) &size, sizeof(long long));
  for(long long i = 0; i < size; ++i){
    std::string name = readString(fin);
    results.vertices.insert(name);
    long long edge_count;
    fin.read((char *) &edge_count, sizeof(long long));
    for(long long j = 0; j < edge_count; ++j){
      std::string target = readString(fin);
      long long weight;
      fin.read((char *) &weight, sizeof(long long));
      (results.edges[name])[target] = weight;
    }
  }
  fin.close();
}

void Commands05::writeString(std::ofstream& fout, std::string str)
{
  int size = str.size();
  fout.write((char *) &size, sizeof(int));
  char * ch = new char[size];
  fout.write((char *) str.c_str(), sizeof(char)*size);
}

void Commands05::writeBuildGraphResults(std::string filename, IGraph * results)
{
  std::ofstream fout(filename.c_str(), std::ios::binary);
  if(fout.good() == false){
    return;
  }

  std::vector<IVertex *> vertices = results->getVertices();
  long long size = vertices.size();
  fout.write((char *) &size, sizeof(long long));
  for(long long i = 0; i < size; ++i){
    IVertex * curr = vertices[i];
    writeString(fout, curr->getName());
    std::vector<IEdge *> edges = curr->getEdges();
    long long edge_count = edges.size();
    fout.write((char *) &edge_count, sizeof(long long));
    for(long long j = 0; j < edge_count; ++j){
      IEdge * edge = edges[j];
      writeString(fout, edge->getTarget()->getName());
      long long weight = (long long) edge->getWeight();
      fout.write((char *) &weight, sizeof(long long));
    }
  }
  fout.close();
}
