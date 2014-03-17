
#include "Vertex.h"

void Vertex::setName(std::string name){
    this->name = name;
}

std::string Vertex::getName(){
    return this->name;
    }

void Vertex::addEdge(IEdge *edge){
    this->edges.push_back(edge);
    }

std::vector<IEdge*> Vertex::getEdges(){
    return this->edges;
    }
