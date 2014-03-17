#include "DoubleNode.h"
using namespace std;

void DoubleNode::setValue(int value){
    this->value = value;
}
void DoubleNode::setWords(std::string word){
    words1->push_back(word);
}
IVectorString* DoubleNode::getWords(){
    return this->words1;
}
int DoubleNode::getValue(){
    return this->value;
}
DoubleNode* DoubleNode::getPrev(){
    return this->prev;
}
DoubleNode* DoubleNode::getNext(){
    return this->next;
}
void DoubleNode::setPrev(DoubleNode* prev){
    this->prev = prev;
}
void DoubleNode::setNext(DoubleNode* next){
    this->next = next;
}
