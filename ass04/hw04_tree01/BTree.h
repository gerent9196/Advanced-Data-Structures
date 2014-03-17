#pragma once
#include "Interfaces04.h"
#include "BTreeNode.h"
#include "vector.h"

class BTree: public IBTree{
public:
    BTreeNode *root;
    std::vector<IBTreeNode*> path;
    std::vector<int> index;
    BTree() {
    root=NULL;
 }                                                                                          
    ~BTree() { }
public:
    void insert(int key, int num_keys);
    void remove(int key, int num_keys);                                                       
    int kthMin(int k);
    void swap(std::vector<int> &, int, int);
    void sort(std::vector<int> &);
    IBTreeNode * getRoot();
    IBTreeNode* findLeafNode(int , IBTreeNode* );
    IBTreeNode* findLeafNodeForRemove(int, IBTreeNode*);
    int find_kth_min(int k, IBTreeNode* curr);
    int countNodes(IBTreeNode* curr);
};
