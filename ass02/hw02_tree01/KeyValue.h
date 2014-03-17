#pragma once

#include "Interfaces02.h"
#include <string>
using  namespace std;

class KeyValue : public IKeyValue{
    public:
        int key;
        IKeyValue *parent;
        int degree;
        IKeyValue *left;
        IKeyValue *right;
        std::string value;

        KeyValue(){}
        ~KeyValue(){}

        void setKey(int key);
        void setValue(std::string value);
        int getKey();
        std::string getValue();
        void setParent(IKeyValue *parent);
        IKeyValue* getParent();
        void setLeft(IKeyValue *left);
        IKeyValue* getLeft();
        void setRight(IKeyValue *right);
        IKeyValue* getRight();
        void setDegree(int degree);
        int getDegree();
};
