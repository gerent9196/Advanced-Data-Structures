#include "Graph.h"
#include "Vertex.h"

IVertex* Graph::insertVertex(std::string name){
        IVertex * vert = new Vertex();
        vert->setName(name);
        this->vertices.push_back(vert);
        return vert;
    }

std::vector<IVertex *> Graph::getVertices(){
        return this->vertices;
    }

