#include "VectorKeyValue.h"
#include "Interfaces02.h"
#include "KeyValue.h"
#include<string.h>

using namespace std;

void VectorKeyValue::push_back(IKeyValue *item){
    if(this->length == this->used){
        //increase length by 2
        IKeyValue **temp_items = new IKeyValue*[this->length*2];
        (this->length)*=2;
        //copy items to tempitems
        std::copy(this->items, this->items + used, temp_items);
        delete[] this->items;
        this->items = temp_items;
    }
       this->items[used] = item;
       (this->used)++;
}
void VectorKeyValue::pop_back(){
   this->used-=1;
}
IKeyValue * VectorKeyValue::get(int index){
    return this->items[index];
}
void VectorKeyValue::set(int index, IKeyValue *item){
    this->items[index] = item;
}
size_t VectorKeyValue::size(){
    return this->used;
}
