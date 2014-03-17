#pragma once

#include "Interfaces05.h"
#include <vector>

class Vertex: public IVertex{
    private:
        std::string name;
        std::vector<IEdge*> edges;
    public:
         Vertex() { }
         ~Vertex() { }
        void setName(std::string name);
        std::string getName();
        void addEdge(IEdge *edge);
        std::vector<IEdge *> getEdges(); 
};
