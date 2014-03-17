#include "RecordsSearch.h"
#include <vector>
#include <iostream>
#include <stdio.h>
using namespace std;
void RecordsSearch::bulkInsert(std::vector<Employee> records){
    for(int i=0; i<records.size(); i++){
        int hash = hash_function(records.at(i).first_name);
        int l_hash = hash_function(records.at(i).last_name);
        int p_hash = hash_function(records.at(i).password);
        std::vector<Employee>* x = f_list[hash] ;
        x->push_back(records.at(i));
        x = l_list[hash] ;
        x->push_back(records.at(i));
        x = p_list[hash] ;
        x->push_back(records.at(i));
    }
}
Employee RecordsSearch::searchFirstName(std::string first_name){
    int hash = hash_function(first_name);
    std::vector<Employee>* x = f_list[hash];
    for(int i=0; i< x->size(); i++){
        if(x->at(i).first_name == first_name){
            return x->at(i);
        }
    }
}

Employee RecordsSearch::searchLastName(std::string last_name){
    int hash = hash_function(last_name);
    std::vector<Employee>* x = l_list[hash];
    for(int i=0; i< x->size(); i++){
        if(x->at(i).last_name == last_name){
            return x->at(i);
        }
    }
}

Employee RecordsSearch::searchPassword(std::string password){
    int hash = hash_function(password);
    std::vector<Employee>* x = p_list[hash];
    for(int i=0; i< x->size(); i++){
        if(x->at(i).password == password){
            return x->at(i);
        }
    }
}

int RecordsSearch::hash_function(std::string chars){
    int length = chars.size();
    char *p = &chars[0];

    long int hash = 0;
    for(int i=0; i<length-1; i++){
        hash += int(p[i]) * ( 31^(length-1-i));
    }
    return(hash % 50);
}


