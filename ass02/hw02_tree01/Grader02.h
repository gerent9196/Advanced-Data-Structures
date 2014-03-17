#pragma once

#include "Interfaces02.h"
#include "AbstractGrader.h"
#include "Date.h"
#include <vector>
#include <string>
#include "Random.h"

class Grader02 : public AbstractGrader {
public:
  virtual int size();
  virtual std::string getDescription(int test_case);
  virtual int getPoints(int test_case);
  virtual Date getDueDate();
  virtual TestCase * grade(int index);
private:
  TestCase * testWorkload1(int len, int order);
  TestCase * testWorkload2(int len, int order);
  TestCase * testWorkload3(int len, int order, int merge_len, int merge_count);
  TestCase * testWorkload4(int len, int order, int merge_len, int merge_count);

  Random m_Random;
};
