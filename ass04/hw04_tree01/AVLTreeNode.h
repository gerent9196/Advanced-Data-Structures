#pragma once
#include "Interfaces04.h"

class AVLTreeNode : public IAVLTreeNode{
    private:
        int key;
        IAVLTreeNode* left;
        IAVLTreeNode* right;
    public:
        AVLTreeNode(){}
        AVLTreeNode(int key);
        ~AVLTreeNode(){}
        void setLeft(IAVLTreeNode * left) ;
        void setRight(IAVLTreeNode * right) ;
        void setKey(int key) ;
        IAVLTreeNode * getLeft() ;
        IAVLTreeNode * getRight() ;
        int getKey() ; 
};
