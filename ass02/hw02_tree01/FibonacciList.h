#pragma once

#include "Interfaces02.h"
#include "VectorKeyValue.h"
#include "VectorBnode.h"
#include "KeyValue.h"
#include "vector.h"

class FibonacciList{
    public:
        int count;
        int level;
        Bnode* lowest_val;
        VectorBnode*  header ;
        void merge(FibonacciList *list1);
        VectorBnode* getHeader();
        Bnode* merge_fibonacci(Bnode* n1, Bnode* n2);
        void add_to_fibonacci(IKeyValue *n1);
        FibonacciList(FibonacciList *other);
        void print();
        void check_header();
        void delete_node();
        void  recursive_delete(Bnode* right_to_left_to_del);

   FibonacciList(){
        count = 1;
        header = new VectorBnode();
        level = 1;
    }
    
};
