#include "Edge.h"

IVertex * Edge::getTarget(){
    return this->target;
    }
void  Edge::setTarget(IVertex * target){
    this->target = target;
    }
int Edge::getWeight(){
    return this->weight;
    }
void Edge::setWeight(int value){
    this->weight = value;
    }
