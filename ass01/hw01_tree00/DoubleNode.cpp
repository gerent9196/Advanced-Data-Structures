#include "DoubleNode.h"

void DoubleNode::setValue(int value){
    this->value = value;
}
int DoubleNode::getValue(){
    return this->value;
}
IDoubleNode* DoubleNode::getPrev(){
    return this->prev;
}
IDoubleNode* DoubleNode::getNext(){
    return this->next;
}
void DoubleNode::setPrev(IDoubleNode* prev){
    this->prev = prev;
}
void DoubleNode::setNext(IDoubleNode* next){
    this->next = next;
}
