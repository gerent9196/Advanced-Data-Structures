#pragma once

#include "Interfaces03.h"
#include "AbstractGrader.h"
#include "Date.h"
#include <vector>
#include <string>
#include "Random.h"

struct EmployeeCmd {
  int action;
  std::string str;
  Employee ret;
};

class Grader03 : public AbstractGrader {
public:
  virtual int size();
  virtual std::string getDescription(int test_case);
  virtual int getPoints(int test_case);
  virtual Date getDueDate();
  virtual TestCase * grade(int index);
private:
  TestCase * testVectorDoubleSort(std::string input_filename, std::string obj_filename);
  TestCase * testSmoothSort(std::string input_filename, std::string heap_filename);
  TestCase * testLinkedListSort(std::string input_filename);
  TestCase * testRunningMedian(std::string input_filename, std::string output_filename, int window_size);
  TestCase * testEmployeeRecords(std::string input_filename, std::string input_cmd_filename);

  void loadEmployeeCommands(std::string input_filename, std::vector<EmployeeCmd>& cmds);
  void loadEmployees(std::string input_filename, std::vector<Employee>& employees);

  Random m_Random;
};
