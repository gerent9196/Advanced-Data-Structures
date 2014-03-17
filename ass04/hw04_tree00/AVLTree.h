#pragma once

#include "Interfaces04.h"
#include "AVLTreeNode.h"

class AVLTree : public IAVLTree {
    
    public:
    IAVLTreeNode* root;
    AVLTree() {
        root = NULL;
     }
    virtual ~AVLTree() { }
    void insert(int key);
    void remove(int key);
    int kthMin(int k);
    IAVLTreeNode * getRoot();
    int calcHeight(IAVLTreeNode* curr);
    int diffHeight(IAVLTreeNode* curr);
    void leftRightRotate(IAVLTreeNode*,IAVLTreeNode* );
    void rightLeftRotate(IAVLTreeNode*, IAVLTreeNode*);
    void rightRightRotate(IAVLTreeNode* );
    void leftLeftRotate(IAVLTreeNode* );
    void print(IAVLTreeNode* );
};
