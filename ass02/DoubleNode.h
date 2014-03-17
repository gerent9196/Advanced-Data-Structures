#include "Interfaces02.h"
#include "VectorString.h"
#include <string>

class DoubleNode{
    public:
        int value;
        IVectorString *words;
        DoubleNode* next;
        DoubleNode* prev;

        DoubleNode(){
           this->words = new VectorString(); 
        }
        
        ~DoubleNode(){}
        void setValue(int value);
        int getValue();
        
        void setWords(std::string word);
        IVectorString* getWords();
        DoubleNode* getPrev();
        DoubleNode* getNext();
        void setPrev(DoubleNode* prev);
        void setNext(DoubleNode* next);
};
