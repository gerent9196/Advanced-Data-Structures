#include "SingleNode.h"

void SingleNode::setValue(int value1){
    value = value1;
}

int SingleNode::getValue(){
    return value;
}

ISingleNode*  SingleNode::getNext(){
    return next;
}

void SingleNode::setNext(ISingleNode *nex){
    next = nex;
}
