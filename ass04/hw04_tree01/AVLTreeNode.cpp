#include "AVLTreeNode.h"
#include <iostream>

//constructor

AVLTreeNode::AVLTreeNode(int key){
    this->key = key;
    this->left = NULL;
    this->right = NULL;
}


//methods
void AVLTreeNode::setLeft(IAVLTreeNode * left){
    this->left = left;
}

void AVLTreeNode::setRight(IAVLTreeNode * right){
    this->right = right;
}
void AVLTreeNode::setKey(int key){
    this->key = key;
}
IAVLTreeNode * AVLTreeNode::getLeft(){
    return this->left;
}
IAVLTreeNode * AVLTreeNode::getRight(){
    return this->right;
}
int AVLTreeNode::getKey(){
    return this->key;
}
