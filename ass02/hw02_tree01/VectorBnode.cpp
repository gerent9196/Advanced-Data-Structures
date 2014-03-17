#include "VectorBnode.h"
#include<string.h>
#include <iostream>

using namespace std;

void VectorBnode::push_back(Bnode *item){
    if(this->length == this->used){
        //increase length by 2
        Bnode **temp_items = new Bnode*[this->length*2];
        (this->length)*=2;
        //copy items to tempitems
        std::copy(this->items, this->items + used, temp_items);
        delete[] this->items;
        this->items = temp_items;
    }
       this->items[used] = item;
       (this->used)++;
}
void VectorBnode::pop_back(){
   this->used-=1;
}
Bnode * VectorBnode::get(int index){
    return this->items[index];
}
void VectorBnode::set(int index, Bnode *item){
    this->items[index] = item;
}
size_t VectorBnode::size(){
    return this->used;
}
