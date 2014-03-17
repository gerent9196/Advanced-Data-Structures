#pragma once

#include "Interfaces07.h"
#include "AbstractGrader.h"
#include "Date.h"
#include <vector>
#include <string>
#include <set>
#include "Random.h"
#include "Commands07.h"

class Grader07 : public AbstractGrader {
public:
  virtual int size();
  virtual std::string getDescription(int test_case);
  virtual int getPoints(int test_case);
  virtual Date getDueDate();
  virtual TestCase * grade(int index);
private:
  TestCase * testStringSearch(std::string cmds_filename, std::string input_filename);
  TestCase * testStringSort(std::string input_filename);
  TestCase * testSpellCheck(std::string filename);
  TestCase * testCompress(std::string input_filename, std::string output_filename);
  TestCase * testDecompress(std::string input_filename, std::string output_filename);
};
