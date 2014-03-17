#include <string>
#include <cstring>
#include <cstdlib>
#include <sstream>
#include <algorithm>
#include <iostream>
#include "Interfaces03.h"
#include "TestCase.h"
#include "Stopwatch.h"
#include "Grader03.h"
#include "vector.h"
#include <cmath>
#include <fstream>

TestCase * Grader03::testVectorDoubleSort(std::string input_filename, std::string obj_filename)
{
  std::vector<double> unsorted;
  std::vector<double> sorted;

  loadBinarySequence(input_filename, unsorted);
  sorted = unsorted;

  Stopwatch watch;
  watch.start();
  IVectorDoubleSort * sorter = (IVectorDoubleSort *) createObject(obj_filename);
  if(sorter == NULL){
    return nullObject(obj_filename);
  }
  
  sorter->sort(unsorted);
  watch.stop();

  std::sort(sorted.begin(), sorted.end());

  for(int i = 0; i < sorted.size(); ++i){
    if(sorted[i] != unsorted[i]){
      return failed("sort does not match");
    }
  }

  return passed(watch.getTime());
}
 
TestCase * Grader03::testSmoothSort(std::string input_filename, std::string heap_filename)
{
  std::vector<double> smooth_input;
  std::vector<double> smooth_heap;

  loadBinarySequence(input_filename, smooth_input);
  loadBinarySequence(heap_filename, smooth_heap);

  Stopwatch watch;
  watch.start();
  ISmoothSort * sorter = (ISmoothSort *) createObject("ISmoothSort");
  if(sorter == NULL){
    return nullObject("ISmoothSort");
  }
  
  sorter->buildHeap(smooth_input);
  watch.pause();

  if(vectorEqual(smooth_input, smooth_heap) == false){
    return failed("build heap incorrect"); 
  }

  watch.unpause();
  sorter->sort(smooth_input);
  watch.pause();
  
  std::sort(smooth_heap.begin(), smooth_heap.end());

  if(vectorEqual(smooth_input, smooth_heap) == false){
    return failed("sort incorrect"); 
  }

  return passed(watch.getTime());
}
  
TestCase * Grader03::testLinkedListSort(std::string input_filename)
{
  std::vector<double> input_vec;

  loadBinarySequence(input_filename, input_vec);

  std::map<double, LinkedListNode *> pointers;

  LinkedListNode * head;
  LinkedListNode * curr;

  head = new LinkedListNode();
  head->key = input_vec[0];
  pointers[input_vec[0]] = head;
  
  curr = new LinkedListNode();
  curr->key = input_vec[1];
  pointers[input_vec[1]] = curr;

  head->next = curr;

  for(size_t i = 2; i < input_vec.size(); ++i){
    double value = input_vec[i];
    LinkedListNode * next = new LinkedListNode();
    next->key = value;
    next->next = NULL;
    pointers[value] = next;
    curr->next = next;
    curr = next;
  }

  Stopwatch watch;
  watch.start();

  ILinkedListSort * sorter = (ILinkedListSort *) createObject("ILinkedListSort");
  if(sorter == NULL){
    return nullObject("ILinkedListSort");
  }

  LinkedListNode * new_head = sorter->sort(head);
  watch.stop();

  std::sort(input_vec.begin(), input_vec.end());

  curr = new_head;

  for(size_t i = 0; i < input_vec.size(); ++i){
    if(curr == NULL){
      return failed("null curr during iteration");
    }
    double key = curr->key;
    if(pointers[key] != curr){
      return failed("must move pointers and not keys");
    }
    if(key != input_vec[i]){
      return failed("incorrect key");
    }
    curr = curr->next;
  }
  return passed(watch.getTime());
}

TestCase * Grader03::testRunningMedian(std::string input_filename, 
  std::string output_filename, int window_size)
{

  std::vector<int> input_vec;
  std::vector<int> output_vec;

  loadBinarySequence(input_filename, input_vec);
  loadBinarySequence(output_filename, output_vec);

  Stopwatch watch;
  watch.start();

  IRunningMedian * running = (IRunningMedian *) createObject("IRunningMedian");
  if(running == NULL){
    return nullObject("IRunningMedian");
  }

  std::vector<int> user_output = running->compute(input_vec, window_size);
  watch.stop();

  if(vectorEqual(output_vec, user_output) == false){
    return failed("result incorrect"); 
  }

  return passed(watch.getTime());
}

std::string readString(std::ifstream& fin)
{
  int size;
  fin.read((char *) &size, sizeof(int));
  char * ch = new char[size+1];
  fin.read((char *) ch, sizeof(char)*size);
  ch[size] = 0;
  std::string ret(ch);
  delete [] ch;
  return ret;
}

void Grader03::loadEmployees(std::string input_filename, 
  std::vector<Employee>& emps)
{
  std::ifstream fin(input_filename.c_str(), std::ios::binary);
  if(fin.good() == false){
    return;
  }
  long long len;
  fin.read((char *) &len, sizeof(long long));
  for(long long i = 0; i < len; ++i){
    std::string first_name = readString(fin);
    std::string last_name = readString(fin);
    std::string password = readString(fin);
    Employee emp;
    emp.first_name = first_name;
    emp.last_name = last_name;
    emp.password = password;
    emps.push_back(emp);
  }
  fin.close();
}

void Grader03::loadEmployeeCommands(std::string input_filename, 
  std::vector<EmployeeCmd>& cmds)
{
  std::ifstream fin(input_filename.c_str(), std::ios::binary);
  if(fin.good() == false){
    return;
  }
  long long len;
  fin.read((char *) &len, sizeof(long long));
  for(long long i = 0; i < len; ++i){
    int action;
    fin.read((char *) &action, sizeof(int));
    std::string str = readString(fin);
    std::string first_name = readString(fin);
    std::string last_name = readString(fin);
    std::string password = readString(fin);
    EmployeeCmd cmd;
    cmd.action = action;
    cmd.str = str;
    cmd.ret.first_name = first_name;
    cmd.ret.last_name = last_name;
    cmd.ret.password = password;
    cmds.push_back(cmd);
  }
  fin.close();
}

bool matches(Employee& lhs, Employee& rhs){
  if(lhs.first_name != rhs.first_name){
    std::cout << "fname" << std::endl;
    std::cout << "  lhs: " << lhs.first_name << std::endl;
    std::cout << "  rhs: " << rhs.first_name << std::endl;
    return false;
  }
  if(lhs.last_name != rhs.last_name){
    std::cout << "lname" << std::endl;
    return false;
  }
  if(lhs.password != rhs.password){
    std::cout << "password" << std::endl;
    return false;
  }
  return true;
} 

TestCase * Grader03::testEmployeeRecords(std::string input_filename, std::string input_cmd_filename)
{
  std::vector<Employee> input_vec;
  loadEmployees(input_filename, input_vec);
  std::vector<EmployeeCmd> commands;
  loadEmployeeCommands(input_cmd_filename, commands);
  
  Stopwatch watch;
  watch.start();

  IRecordsSearch * records = (IRecordsSearch *) createObject("IRecordsSearch");
  if(records == NULL){
    return nullObject("IRecordsSearch");
  }

  records->bulkInsert(input_vec);

  int FIRST_NAME = 0;
  int LAST_NAME = 1;
  int PASSWORD = 2;

  for(size_t i = 0; i < commands.size(); ++i){
    EmployeeCmd cmd = commands[i];
    if(cmd.action == FIRST_NAME){
      Employee employ = records->searchFirstName(cmd.str);
      if(matches(employ, cmd.ret) == false){
        return failed("search first_name mismatch");
      }
    } else if(cmd.action == LAST_NAME){
      Employee employ = records->searchLastName(cmd.str);
      if(matches(employ, cmd.ret) == false){
        return failed("search last_name mismatch");
      }
    } else if(cmd.action == PASSWORD){
      Employee employ = records->searchPassword(cmd.str);
      if(matches(employ, cmd.ret) == false){
        return failed("search password mismatch");
      }
    }
  }

  watch.stop();
  return passed(watch.getTime());
}

int Grader03::size(){
  return 10;
}

std::string Grader03::getDescription(int test_case)
{
  switch(test_case){
  case 0: return "vector double sort1";
  case 1: return "vector double sort2";
  case 2: return "smoothsort small";
  case 3: return "smoothsort large";
  case 4: return "linked-list sort small";
  case 5: return "linked-list sort large";
  case 6: return "running median small";
  case 7: return "running median large";
  case 8: return "employee records small";
  case 9: return "employee records large";
  }
  return "";
}

int Grader03::getPoints(int test_case)
{
  switch(test_case){
  case 0: return 10;
  case 1: return 10;
  case 2: return 10;
  case 3: return 10;
  case 4: return 10;
  case 5: return 10;
  case 6: return 10;
  case 7: return 10;
  case 8: return 10;
  case 9: return 10;
  }
  return 0;
}

Date Grader03::getDueDate()
{
  return Date(10, 17, 2013);
}
  
TestCase * Grader03::grade(int index){
  switch(index){
  case 0:
    return testVectorDoubleSort("workload1.bin", "IVectorDoubleSort1");
  case 1:
    return testVectorDoubleSort("workload2.bin", "IVectorDoubleSort2");
  case 2:
    return testSmoothSort("smooth_input_small.bin", "smooth_heap_small.bin");
  case 3:
    return testSmoothSort("smooth_input_large.bin", "smooth_heap_large.bin");
  case 4:
    return testLinkedListSort("linked_list_input_small.bin");
  case 5:
    return testLinkedListSort("linked_list_input_large.bin");
  case 6:
    return testRunningMedian("median_input_small.bin", "median_output_small.bin", 10);
  case 7:
    return testRunningMedian("median_input_large.bin", "median_output_large.bin", 1000);
  case 8:
    return testEmployeeRecords("records_small.bin", "records_cmds_small.bin");
  case 9:
    return testEmployeeRecords("records_large.bin", "records_cmds_large.bin");
  default:
    return NULL;
  }
}
