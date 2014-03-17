#include "VectorString.h"
#include<string.h>

using namespace std;

void VectorString::push_back(std::string item){
    if(this->length == this->used){
        //increase length by 2
        std::string *temp_words= new std::string[this->length*2];
        this->length*=2;
        //copy words to tempwords
        std::copy(words, (words + used), temp_words);
        delete[] words;
        words = temp_words;
    }
        words[(this->used)] = item;
        this->used++;
}

void VectorString::pop_back(){
   this->used-=1;
}
 std::string VectorString::get(int index){
    return words[index];
}
 void VectorString::set(int index, std::string item){
    this->words[index] = item;
}
size_t VectorString::size(){
    return this->used;
}
