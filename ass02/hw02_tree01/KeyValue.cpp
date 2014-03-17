#include "KeyValue.h"


void KeyValue::setKey(int key){
    this->key = key;
}

void KeyValue::setValue(std::string val){
    value = val;
}

int KeyValue::getKey(){
    return this->key;
}

std::string KeyValue::getValue(){
    return this->value;
}

void KeyValue::setParent(IKeyValue *parent){
    this->parent = parent;
}
IKeyValue* KeyValue::getParent(){
    return this->parent ;
}

void KeyValue::setLeft(IKeyValue *left){
    this->left = left;
}
IKeyValue*  KeyValue::getLeft(){
    return this->left ;
}

void KeyValue::setRight(IKeyValue *right){
    this->right = right;
}
IKeyValue* KeyValue::getRight(){
    return this->right ;
}

void KeyValue::setDegree(int degree){
    this->degree = degree;
}
int KeyValue::getDegree(){
    return this->degree ;
}
