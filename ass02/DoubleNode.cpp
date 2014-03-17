#include "DoubleNode.h"
using namespace std;


void DoubleNode::setWords(std::string word){
    words->push_back(word);
}

IVectorString* DoubleNode::getWords(){
    return this->words;
}
void DoubleNode::setValue(int value){
    this->value = value;
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
