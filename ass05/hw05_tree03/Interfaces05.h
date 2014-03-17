#pragma once

#include <vector>
#include <cstdlib>
#include <string>

struct IVertex;

struct IEdge {
  IEdge() { }
  virtual ~IEdge() { }
  virtual IVertex * getTarget() = 0;
  virtual void setTarget(IVertex * target) = 0;
  virtual int getWeight() = 0;
  virtual void setWeight(int value) = 0;
};

struct IVertex {
  IVertex() { }
  virtual ~IVertex() { }
  virtual void setName(std::string name) = 0;
  virtual std::string getName() = 0;
  virtual void addEdge(IEdge * edge) = 0;
  virtual std::vector<IEdge *> getEdges() = 0;
};

struct IGraph {
  IGraph() { }
  virtual ~IGraph() { }
  virtual IVertex * insertVertex(std::string name) = 0;
  virtual std::vector<IVertex *> getVertices() = 0;
};

struct ISequencer {
  ISequencer() { }
  virtual ~ISequencer() { }
  virtual IGraph * buildGraph(std::vector<std::string>& reads) = 0;
  virtual std::vector<std::string> tsp(std::string start_read, IGraph * graph) = 0;
  virtual std::string assemble(std::vector<std::string>& tsp_result) = 0;
};
