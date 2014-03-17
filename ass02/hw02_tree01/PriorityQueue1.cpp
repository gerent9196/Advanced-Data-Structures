#include "PriorityQueue1.h"
#include "VectorKeyValue.h"


void PriorityQueue1::enqueue(IKeyValue * key_value){
    l->addSorted(key_value->getKey(), key_value->getValue());
}

void PriorityQueue1::merge(IPriorityQueue * input_queue){
}

IVectorKeyValue* PriorityQueue1::returnSorted(){
    DoubleNode *temp_head = l->head;
    IVectorKeyValue *ivk = new VectorKeyValue();
    while(temp_head!=NULL){

        int key = temp_head->getValue();
        
        IVectorString *kv_s = (temp_head->getWords());
        size_t kv_size = kv_s->size();

        for(int i = 0; i< kv_size; i++){
            IKeyValue *kv = new KeyValue();
            kv->setKey(key);
            kv->setValue(kv_s->get(i));
            ivk->push_back(kv);
        }
        temp_head = temp_head->getNext();
    }
    return ivk;

}

int PriorityQueue1::lowestKey(){
    return (l->head)->getValue();
}

IVectorString* PriorityQueue1::lowestValues(){
    for(int i = 0; i< ((l->head)->getWords())->size() ; i++)
    return (l->head)->getWords();
}

void PriorityQueue1::dequeue(){
    l->delete_root();
}

size_t PriorityQueue1::size(){
    return l->count;
}


