#include "BTreeNode.h"


BTreeNode::BTreeNode(int k) 
{
    keys.push_back(k);
}

BTreeNode::~BTreeNode() {}

int BTreeNode::getKey(int index) {
    return keys[index];
}  

void BTreeNode::setKey(int index, int key) {
    keys[index] = key;
}
int BTreeNode::getKeySize() {
   return keys.size(); 
}
    
void BTreeNode::setKeySize(int size) {
    
}
int BTreeNode::getChildSize() {
    return branches.size();
}

void BTreeNode::setChildSize(int size) {
}

IBTreeNode * BTreeNode::getChild(int index) {
    return branches[index];
}

void BTreeNode::setChild(int index, IBTreeNode * child) {
    branches[index] = child;
}

bool BTreeNode::isLeaf() {
    if(branches.size()>0)
        return false;
    return true;
}
