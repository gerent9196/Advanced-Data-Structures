#pragma once

#include "Interfaces05.h"
#include "AbstractGrader.h"
#include "Date.h"
#include <vector>
#include <string>
#include <set>
#include "Random.h"
#include "Commands05.h"

class Grader05 : public AbstractGrader {
public:
  virtual int size();
  virtual std::string getDescription(int test_case);
  virtual int getPoints(int test_case);
  virtual Date getDueDate();
  virtual TestCase * grade(int index);
private:
  void print(std::vector<std::string>& vec);
  TestCase * testBuildGraph(std::string reads_filename, std::string results_filename);
  TestCase * testTSP(std::string reads_filename, std::string start_read, std::string results_filename);
  TestCase * testAssemble(std::string input_filename, std::string result);

  Random m_Random;
};
