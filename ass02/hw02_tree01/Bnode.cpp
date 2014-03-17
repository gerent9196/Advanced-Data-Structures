#include "Bnode.h"
#include <iostream>

void Bnode::setParent(Bnode *parent){
    this->parent = parent;
}
Bnode* Bnode::getParent(){
    return this->parent ;
}

void Bnode::setLeft(Bnode *left){
    this->left = left;
}
Bnode*  Bnode::getLeft(){
    return this->left ;
}        
          
void Bnode::setRight(Bnode *right){
    this->right = right; 
}
Bnode* Bnode::getRight(){
    return this->right ;
}
void Bnode::setDegree(int degree){
    this->degree = degree; 
}   
int Bnode::getDegree(){
    return this->degree ;
}  

IKeyValue* Bnode::getKeyValue(){
    return this->kv;
}

void Bnode::print(){
    cout << " " << "key:" << this->getKeyValue()->getKey();
    cout << " " << "value:" << this->getKeyValue()->getValue();
    cout << " " << "parent:"<<this->parent;
    cout << " " << "left:"<<this->left;
    cout << " " << "right:"<<this->right;
    cout << " " << "degree:"<<this->degree << "\n";
}
