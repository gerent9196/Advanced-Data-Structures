#pragma once

#include <vector>
#include <utility>
#include <string>

struct IVectorDoubleSort {
  IVectorDoubleSort() { }
  virtual ~IVectorDoubleSort() { }
  virtual void sort(std::vector<double>& vec) = 0;  
};

struct ISmoothSort {
  ISmoothSort() { }
  virtual ~ISmoothSort() { }
  virtual void buildHeap(std::vector<double>& vec) = 0;
  virtual void sort(std::vector<double>& vec) = 0;
};

struct LinkedListNode {
  double key;
  LinkedListNode * next;
};

struct ILinkedListSort {
  ILinkedListSort() { }
  virtual ~ILinkedListSort() { }
  virtual LinkedListNode * sort(LinkedListNode * list) = 0;
};

struct IRunningMedian {
  IRunningMedian() { }
  virtual ~IRunningMedian() { }
  virtual std::vector<int> compute(std::vector<int> vec, int window_size) = 0;
};

struct Employee {
  std::string first_name;
  std::string last_name;
  std::string password;
};

struct IRecordsSearch {
  IRecordsSearch() { }
  virtual ~IRecordsSearch() { } 
  virtual void bulkInsert(std::vector<Employee> records) = 0;
  virtual Employee searchFirstName(std::string first_name) = 0;
  virtual Employee searchLastName(std::string last_name) = 0;
  virtual Employee searchPassword(std::string password) = 0;
};
