#pragma once

#include "Interfaces03.h"
#include<vector>
using namespace std;

 

class RecordsSearch: public IRecordsSearch { 
  public:
  std::vector<Employee> emp;
  /*
  struct Hash_entry{
    std::vector<Employee> records;
  };
  */
  
 // Hash_entry** f_name;
  
  RecordsSearch(){
    //f_name = new Hash_entry*[2000];
    /*
    f_list = new std::vector<Employee>*[50];
    for(int i=0; i<50; i++){
        f_list[i]= new std::vector<Employee>;
    }
    l_list = new std::vector<Employee>*[50];
    for(int i=0; i<50; i++){
        l_list[i]= new std::vector<Employee>;
    }
    p_list = new std::vector<Employee>*[50];
    for(int i=0; i<50; i++){
        p_list[i]= new std::vector<Employee>;
    }
    */
  }
  ~RecordsSearch() { }
  void bulkInsert(std::vector<Employee> records);
  Employee searchFirstName(std::string first_name);
  Employee searchLastName(std::string last_name);
  Employee searchPassword(std::string password);
  int hash_function(std::string chars);
};
