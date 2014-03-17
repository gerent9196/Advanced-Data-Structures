#pragma once



class TSPNode{
   public:
    IVertex* start;
    std::vector<IVertex*> path;
    int weight;
    TSPNode(){
    }
    TSPNode(IVertex* vert){
        start = vert;
        path.push_back(vert);
        weight = 0;
    }
    ~TSPNode(){
    }
};
