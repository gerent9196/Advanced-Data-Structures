#pragma once

#include "Interfaces02.h"
#include "VectorKeyValue.h"
#include "VectorBnode.h"
#include "KeyValue.h"
#include "vector.h"

class BinomialList{
    public:
        int count;
        int level;
        VectorBnode*  header ;
        void merge(BinomialList *list1);
        VectorBnode* getHeader();
        Bnode* merge_binomial(Bnode* n1, Bnode* n2);
        void add_to_binomial(IKeyValue *n1);
        BinomialList(BinomialList *other);
        void print();
        void check_header();
        void delete_node();
        void  recursive_delete(Bnode* right_to_left_to_del);

   BinomialList(){
        count = 1;
        header = new VectorBnode();
        level = 1;
    }
    
};
