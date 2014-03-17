#pragma once

#include <string>
#include "Interfaces02.h"
#include "KeyValue.h"

class Bnode{
    public:
        Bnode *parent;
        IKeyValue *kv;
        int degree;
        Bnode *left;
        Bnode *right;
        Bnode(){
        }
        Bnode(IKeyValue *kv){
            this->kv = kv;
            this->left = NULL;
            this->right = NULL;
            this->degree = 1;
            this->parent = NULL;
        }
        ~Bnode(){
        }

        void setParent(Bnode *parent);
        Bnode* getParent();

        void setLeft(Bnode *left);
        Bnode* getLeft();
        void setRight(Bnode *right);
        Bnode* getRight();

        void setDegree(int);
        int getDegree();
        IKeyValue* getKeyValue();
        void print();
};
