#pragma once

#include "Interfaces02.h"

class VectorString : public IVectorString{
    public:
         size_t length;
         size_t used;
         std::string *words;
         VectorString(){
            this->length = 1;
            this->used = 0;
            this->words = new std::string[1];
         }
         ~VectorString(){
         }
         void push_back(std::string item);
         void pop_back();
         std::string get(int index);
         void set(int index, std::string item);
         size_t size();
};
