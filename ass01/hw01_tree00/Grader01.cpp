#include <string>
#include <cstring>
#include <vector>
#include <stack>
#include <iostream>
#include <algorithm>
#include "TestCase.h"
#include "Stopwatch.h"
#include "Interfaces01.h"
#include "Grader01.h"

void Grader01::createOriginalSequence(int len, std::vector<int>& ret){
  for(int i = 0; i < len; ++i){
    ret.push_back(i);
  }
}

void Grader01::createReverseSequence(int len, std::vector<int>& ret){
  for(int i = len - 1; i >= 0; --i){
    ret.push_back(i);
  }
}

void Grader01::createReverse(std::vector<int>& original, std::vector<int>& ret){
  for(int i = original.size() - 1; i >= 0; --i){
    ret.push_back(original[i]);
  }
}

void Grader01::createRandomSequence(int len, std::vector<int>& ret){
  m_random.randomVector(len, ret);
}

void Grader01::createOrderSort2(std::vector<int>& original, std::vector<int>& ret){
  for(int i = 0; i < original.size() - 1; i += 2){
    int entry1 = original[i];
    int entry2 = original[i+1];
    ret.push_back(entry2);
    ret.push_back(entry1);
  }
}

void Grader01::createOrderSort3(std::vector<int>& original, std::vector<int>& ret){
  for(int i = 0; i < original.size() - 2 || i < original.size() - 1; i += 3){
    int entry1 = original[i];
    int entry2 = original[i+1];
    if(i + 2 < original.size()){
      int entry3 = original[i+2];
      ret.push_back(entry3);
    }
    ret.push_back(entry2);
    ret.push_back(entry1);
  }
}
  
void Grader01::createSequenceOrderSort(std::vector<int>& original, std::vector<int>& ret){
  int step_size = 2;
  for(int i = 0; i < original.size(); ){
    std::stack<int> stk;
    for(int j = 0; j < step_size && i + j < original.size(); ++j){
      stk.push(original[i+j]);
    }
    while(stk.size() > 0){
      int entry = stk.top();
      stk.pop();
      ret.push_back(entry);
    }
    i += step_size;
    ++step_size;
  }
}

TestCase * Grader01::singleOrderSort2(int len){
  std::vector<int> org_seq;
  std::vector<int> order_seq;

  createOriginalSequence(len, org_seq);
  createOrderSort2(org_seq, order_seq);

  Stopwatch watch;
  watch.start();

  std::map<ISingleNode *, int> pointers;
  ISingleList * single_list = (ISingleList *) createObject("ISingleList");
  if(single_list == NULL){
    return nullObject("ISingleList");
  }
  for(int i = org_seq.size() - 1; i >= 0; --i){
    int value = org_seq[i];
    single_list->addHead(value);
    ISingleNode * head = single_list->getHead();
    watch.pause();
    pointers[head] = value;

    if(head->getValue() != value){
      return failed("problem with addHead");
    }
    watch.unpause();
  }
  
  single_list->orderSort2();
  watch.stop();

  ISingleNode * curr = single_list->getHead();
  for(int i = 0; i < order_seq.size(); ++i){
    if(curr == NULL){
      return failed("list terminated abruptly");
    }
    int curr_value = curr->getValue();
    if(curr_value != order_seq[i]){
      return failed("order incorrect: [index: "+toString(i)+", given: "+toString(curr_value)+", gold: "+toString(order_seq[i])+"]");
    }
    if(pointers[curr] != curr_value){
      return failed("pointer mismatch");
    }
    curr = curr->getNext();
  }

  return passed(watch.getTime());
}

TestCase * Grader01::singleOrderSort3(int len){
  std::vector<int> org_seq;
  std::vector<int> order_seq;

  createOriginalSequence(len, org_seq);
  createOrderSort3(org_seq, order_seq);

  Stopwatch watch;
  watch.start();

  std::map<ISingleNode *, int> pointers;
  ISingleList * single_list = (ISingleList *) createObject("ISingleList");
  if(single_list == NULL){
    return nullObject("ISingleList");
  }
  for(int i = org_seq.size() - 1; i >= 0; --i){
    int value = org_seq[i];
    single_list->addHead(value);
    ISingleNode * head = single_list->getHead();
    watch.pause();
    pointers[head] = value;

    if(head->getValue() != value){
      return failed("problem with addHead");
    }
    watch.unpause();
  }
  
  single_list->orderSort3();
  watch.stop();

  ISingleNode * curr = single_list->getHead();
  for(int i = 0; i < order_seq.size(); ++i){
    if(curr == NULL){
      return failed("list terminated abruptly");
    }
    int curr_value = curr->getValue();
    if(curr_value != order_seq[i]){
      return failed("order incorrect: [index: "+toString(i)+", given: "+toString(curr_value)+", gold: "+toString(order_seq[i])+"]");
    }
    if(pointers[curr] != curr_value){
      return failed("pointer mismatch");
    }
    curr = curr->getNext();
  }

  return passed(watch.getTime());
}

TestCase * Grader01::singleSequenceOrderSort(int len){
  std::vector<int> org_seq;
  std::vector<int> order_seq;

  createOriginalSequence(len, org_seq);
  createSequenceOrderSort(org_seq, order_seq);

  Stopwatch watch;
  watch.start();

  std::map<ISingleNode *, int> pointers;
  ISingleList * single_list = (ISingleList *) createObject("ISingleList");
  if(single_list == NULL){
    return nullObject("ISingleList");
  }
  for(int i = org_seq.size() - 1; i >= 0; --i){
    int value = org_seq[i];
    single_list->addHead(value);
    ISingleNode * head = single_list->getHead();
    watch.pause();
    pointers[head] = value;

    if(head->getValue() != value){
      return failed("problem with addHead");
    }
    watch.unpause();
  }
  
  single_list->sequenceOrderSort();
  watch.stop();

  ISingleNode * curr = single_list->getHead();
  for(int i = 0; i < order_seq.size(); ++i){
    if(curr == NULL){
      return failed("list terminated abruptly");
    }
    int curr_value = curr->getValue();
    if(curr_value != order_seq[i]){
      return failed("order incorrect: [index: "+toString(i)+", given: "+toString(curr_value)+", gold: "+toString(order_seq[i])+"]");
    }
    if(pointers[curr] != curr_value){
      return failed("pointer mismatch");
    }
    curr = curr->getNext();
  }

  return passed(watch.getTime());
}

TestCase * Grader01::singleReverse(int len){
  std::vector<int> org_seq;
  std::vector<int> order_seq;

  createOriginalSequence(len, org_seq);
  createReverseSequence(len, order_seq);

  Stopwatch watch;
  watch.start();

  std::map<ISingleNode *, int> pointers;
  ISingleList * single_list = (ISingleList *) createObject("ISingleList");
  if(single_list == NULL){
    return nullObject("ISingleList");
  }
  for(int i = org_seq.size() - 1; i >= 0; --i){
    int value = org_seq[i];
    single_list->addHead(value);
    ISingleNode * head = single_list->getHead();
    watch.pause();
    pointers[head] = value;

    if(head->getValue() != value){
      return failed("problem with addHead");
    }
    watch.unpause();
  }
  
  single_list->reverse();
  watch.stop();

  ISingleNode * curr = single_list->getHead();
  for(int i = 0; i < order_seq.size(); ++i){
    if(curr == NULL){
      return failed("list terminated abruptly");
    }
    int curr_value = curr->getValue();
    if(curr_value != order_seq[i]){
      return failed("order incorrect: [index: "+toString(i)+", given: "+toString(curr_value)+", gold: "+toString(order_seq[i])+"]");
    }
    if(pointers[curr] != curr_value){
      return failed("pointer mismatch");
    }
    curr = curr->getNext();
  }

  return passed(watch.getTime());
}

TestCase * Grader01::doubleOrderSort2(int len){
  std::vector<int> org_seq;
  std::vector<int> random_seq;
  std::vector<int> order_seq;

  createRandomSequence(len, random_seq);
  org_seq = random_seq;
  std::sort(org_seq.begin(), org_seq.end());
  createOrderSort2(org_seq, order_seq);

  Stopwatch watch;
  watch.start();

  IDoubleList * double_list = (IDoubleList *) createObject("IDoubleList");
  if(double_list == NULL){
    return nullObject("IDoubleList");
  }
  for(int i = 0; i < random_seq.size(); ++i){
    int value = random_seq[i];
    double_list->addSorted(value);
  }

  IDoubleNode * curr = double_list->getHead();
  watch.pause();

  std::map<IDoubleNode *, int> pointers;
  std::vector<IDoubleNode *> order;

  while(curr != NULL){
    pointers[curr] = curr->getValue();
    order.push_back(curr);
    curr = curr->getNext();
  }

  if(order.size() != len){
    return failed("forward traversal size incorrect");
  }

  watch.unpause();
  curr = double_list->getTail();
  watch.pause();

  std::vector<IDoubleNode *> rorder;
  while(curr != NULL){
    rorder.push_back(curr);
    curr = curr->getPrev();
  }
 
  if(rorder.size() != len){
    return failed("reverse traversal size incorrect");
  }

  for(int i = 0; i < org_seq.size(); ++i){
    int lhs = org_seq[i];
    int rhs = order[i]->getValue();
    if(lhs != rhs){
      return failed("forward traversal is not sorted");
    }
  }

  for(int i = 0; i < org_seq.size(); ++i){
    int lhs = org_seq[org_seq.size() - 1 - i];
    int rhs = rorder[i]->getValue();    
    if(lhs != rhs){
      return failed("reverse traversal is not sorted");
    }
  }

  order.clear();
  rorder.clear();

  watch.unpause();
  double_list->orderSort2();
  IDoubleNode * head = double_list->getHead();
  IDoubleNode * tail = double_list->getTail();
  watch.pause();

  curr = head;
  while(curr != NULL){
    if(pointers[curr] != curr->getValue()){
      return failed("pointer mismatch");
    }
    order.push_back(curr);
    curr = curr->getNext();
  }

  if(order.size() != len){
    return failed("forward traversal size incorrect #2");
  }

  
  for(int i = 0; i < order_seq.size(); ++i){
    int lhs = order_seq[i];
    int rhs = order[i]->getValue();
    if(lhs != rhs){
      return failed("forward traversal is out of final order");
    }
  }

  curr = tail;
  while(curr != NULL){
    if(pointers[curr] != curr->getValue()){
      return failed("pointer mismatch");
    }
    rorder.push_back(curr);
    curr = curr->getPrev();
  }

  for(int i = 0; i < order_seq.size(); ++i){
    int lhs = order_seq[order_seq.size() - 1 - i];
    int rhs = rorder[i]->getValue();    
    if(lhs != rhs){
      return failed("reverse traversal is out of final order");
    }
  }

  return passed(watch.getTime());
}

TestCase * Grader01::doubleOrderSort3(int len){
  std::vector<int> org_seq;
  std::vector<int> random_seq;
  std::vector<int> order_seq;

  createRandomSequence(len, random_seq);
  org_seq = random_seq;
  std::sort(org_seq.begin(), org_seq.end());
  createOrderSort3(org_seq, order_seq);

  Stopwatch watch;
  watch.start();

  IDoubleList * double_list = (IDoubleList *) createObject("IDoubleList");
  if(double_list == NULL){
    return nullObject("IDoubleList");
  }
  for(int i = 0; i < random_seq.size(); ++i){
    int value = random_seq[i];
    double_list->addSorted(value);
  }

  IDoubleNode * curr = double_list->getHead();
  watch.pause();

  std::map<IDoubleNode *, int> pointers;
  std::vector<IDoubleNode *> order;

  while(curr != NULL){
    pointers[curr] = curr->getValue();
    order.push_back(curr);
    curr = curr->getNext();
  }

  if(order.size() != len){
    return failed("forward traversal size incorrect");
  }

  watch.unpause();
  curr = double_list->getTail();
  watch.pause();

  std::vector<IDoubleNode *> rorder;
  while(curr != NULL){
    rorder.push_back(curr);
    curr = curr->getPrev();
  }
 
  if(rorder.size() != len){
    return failed("reverse traversal size incorrect");
  }

  for(int i = 0; i < org_seq.size(); ++i){
    int lhs = org_seq[i];
    int rhs = order[i]->getValue();
    if(lhs != rhs){
      return failed("forward traversal is not sorted");
    }
  }

  for(int i = 0; i < org_seq.size(); ++i){
    int lhs = org_seq[org_seq.size() - 1 - i];
    int rhs = rorder[i]->getValue();    
    if(lhs != rhs){
      return failed("reverse traversal is not sorted");
    }
  }

  order.clear();
  rorder.clear();

  watch.unpause();
  double_list->orderSort3();
  IDoubleNode * head = double_list->getHead();
  IDoubleNode * tail = double_list->getTail();
  watch.pause();

  curr = head;
  while(curr != NULL){
    if(pointers[curr] != curr->getValue()){
      return failed("pointer mismatch");
    }
    order.push_back(curr);
    curr = curr->getNext();
  }

  if(order.size() != len){
    return failed("forward traversal size incorrect #2");
  }
  
  for(int i = 0; i < order_seq.size(); ++i){
    int lhs = order_seq[i];
    int rhs = order[i]->getValue();
    if(lhs != rhs){
      return failed("forward traversal is out of final order");
    }
  }

  curr = tail;
  while(curr != NULL){
    if(pointers[curr] != curr->getValue()){
      return failed("pointer mismatch");
    }
    rorder.push_back(curr);
    curr = curr->getPrev();
  }

  for(int i = 0; i < order_seq.size(); ++i){
    int lhs = order_seq[order_seq.size() - 1 - i];
    int rhs = rorder[i]->getValue();    
    if(lhs != rhs){
      std::cout << "index: " << i << std::endl;
      std::cout << "lhs: " << lhs << std::endl;
      std::cout << "rhs: " << rhs << std::endl;
      for(int j = 0; j < order_seq.size(); ++j){
        std::cout << "order_seq[" << j << "]: " << order_seq[j] << std::endl; 
      }
      return failed("reverse traversal is out of final order");
    }
  }

  return passed(watch.getTime());
}

TestCase * Grader01::doubleSequenceOrderSort(int len){
  std::vector<int> org_seq;
  std::vector<int> random_seq;
  std::vector<int> order_seq;

  createRandomSequence(len, random_seq);
  org_seq = random_seq;
  std::sort(org_seq.begin(), org_seq.end());
  createSequenceOrderSort(org_seq, order_seq);

  Stopwatch watch;
  watch.start();

  IDoubleList * double_list = (IDoubleList *) createObject("IDoubleList");
  if(double_list == NULL){
    return nullObject("IDoubleList");
  }
  for(int i = 0; i < random_seq.size(); ++i){
    int value = random_seq[i];
    double_list->addSorted(value);
  }

  IDoubleNode * curr = double_list->getHead();
  watch.pause();

  std::map<IDoubleNode *, int> pointers;
  std::vector<IDoubleNode *> order;

  while(curr != NULL){
    pointers[curr] = curr->getValue();
    order.push_back(curr);
    curr = curr->getNext();
  }

  if(order.size() != len){
    return failed("forward traversal size incorrect");
  }

  watch.unpause();
  curr = double_list->getTail();
  watch.pause();

  std::vector<IDoubleNode *> rorder;
  while(curr != NULL){
    rorder.push_back(curr);
    curr = curr->getPrev();
  }
 
  if(rorder.size() != len){
    return failed("reverse traversal size incorrect");
  }

  for(int i = 0; i < org_seq.size(); ++i){
    int lhs = org_seq[i];
    int rhs = order[i]->getValue();
    if(lhs != rhs){
      return failed("forward traversal is not sorted");
    }
  }

  for(int i = 0; i < org_seq.size(); ++i){
    int lhs = org_seq[org_seq.size() - 1 - i];
    int rhs = rorder[i]->getValue();    
    if(lhs != rhs){
      return failed("reverse traversal is not sorted");
    }
  }

  order.clear();
  rorder.clear();

  watch.unpause();
  double_list->sequenceOrderSort();
  IDoubleNode * head = double_list->getHead();
  IDoubleNode * tail = double_list->getTail();
  watch.pause();

  curr = head;
  while(curr != NULL){
    if(pointers[curr] != curr->getValue()){
      return failed("pointer mismatch");
    }
    order.push_back(curr);
    curr = curr->getNext();
  }

  if(order.size() != len){
    return failed("forward traversal size incorrect #2");
  }
  
  for(int i = 0; i < order_seq.size(); ++i){
    int lhs = order_seq[i];
    int rhs = order[i]->getValue();
    if(lhs != rhs){
      return failed("forward traversal is out of final order");
    }
  }

  curr = tail;
  while(curr != NULL){
    if(pointers[curr] != curr->getValue()){
      return failed("pointer mismatch");
    }
    rorder.push_back(curr);
    curr = curr->getPrev();
  }

  for(int i = 0; i < order_seq.size(); ++i){
    int lhs = order_seq[order_seq.size() - 1 - i];
    int rhs = rorder[i]->getValue();    
    if(lhs != rhs){
      return failed("reverse traversal is out of final order");
    }
  }

  return passed(watch.getTime());
}

TestCase * Grader01::doubleReverse(int len){
  std::vector<int> org_seq;
  std::vector<int> random_seq;
  std::vector<int> order_seq;

  createRandomSequence(len, random_seq);
  org_seq = random_seq;
  std::sort(org_seq.begin(), org_seq.end());
  createReverse(org_seq, order_seq);

  Stopwatch watch;
  watch.start();

  IDoubleList * double_list = (IDoubleList *) createObject("IDoubleList");
  if(double_list == NULL){
    return nullObject("IDoubleList");
  }
  for(int i = 0; i < random_seq.size(); ++i){
    int value = random_seq[i];
    double_list->addSorted(value);
  }

  IDoubleNode * curr = double_list->getHead();
  watch.pause();

  std::map<IDoubleNode *, int> pointers;
  std::vector<IDoubleNode *> order;

  while(curr != NULL){
    pointers[curr] = curr->getValue();
    order.push_back(curr);
    curr = curr->getNext();
  }

  if(order.size() != len){
    return failed("forward traversal size incorrect");
  }

  watch.unpause();
  curr = double_list->getTail();
  watch.pause();

  std::vector<IDoubleNode *> rorder;
  while(curr != NULL){
    rorder.push_back(curr);
    curr = curr->getPrev();
  }
 
  if(rorder.size() != len){
    return failed("reverse traversal size incorrect");
  }

  for(int i = 0; i < org_seq.size(); ++i){
    int lhs = org_seq[i];
    int rhs = order[i]->getValue();
    if(lhs != rhs){
      return failed("forward traversal is not sorted");
    }
  }

  for(int i = 0; i < org_seq.size(); ++i){
    int lhs = org_seq[org_seq.size() - 1 - i];
    int rhs = rorder[i]->getValue();    
    if(lhs != rhs){
      return failed("reverse traversal is not sorted");
    }
  }

  order.clear();
  rorder.clear();

  watch.unpause();
  double_list->reverse();
  IDoubleNode * head = double_list->getHead();
  IDoubleNode * tail = double_list->getTail();
  watch.pause();

  curr = head;
  while(curr != NULL){
    if(pointers[curr] != curr->getValue()){
      return failed("pointer mismatch");
    }
    order.push_back(curr);
    curr = curr->getNext();
  }

  if(order.size() != len){
    return failed("forward traversal size incorrect #2");
  }
  
  for(int i = 0; i < order_seq.size(); ++i){
    int lhs = order_seq[i];
    int rhs = order[i]->getValue();
    if(lhs != rhs){
      return failed("forward traversal is out of final order");
    }
  }

  curr = tail;
  while(curr != NULL){
    if(pointers[curr] != curr->getValue()){
      return failed("pointer mismatch");
    }
    rorder.push_back(curr);
    curr = curr->getPrev();
  }

  for(int i = 0; i < order_seq.size(); ++i){
    int lhs = order_seq[order_seq.size() - 1 - i];
    int rhs = rorder[i]->getValue();    
    if(lhs != rhs){
      return failed("reverse traversal is out of final order");
    }
  }

  return passed(watch.getTime());
}

int Grader01::size(){
  return 20;
}

std::string Grader01::getDescription(int test_case)
{
  switch(test_case){
  case 0: return "single order sort2 small";
  case 1: return "single order sort2 large";
  case 2: return "single order sort3 small";
  case 3: return "single order sort3 small odd";
  case 4: return "single order sort3 large";
  case 5: return "single sequence order sort small";
  case 6: return "single sequence order sort odd";
  case 7: return "single sequence order sort large";
  case 8: return "single reverse small";
  case 9: return "single reverse large";
  case 10: return "double order sort2 small";
  case 11: return "double order sort2 large";
  case 12: return "double order sort3 small";
  case 13: return "double order sort3 odd";
  case 14: return "double order sort3 large";
  case 15: return "double sequence order sort small";
  case 16: return "double sequence order sort odd";
  case 17: return "double sequence order sort large";
  case 18: return "double reverse small";
  case 19: return "double reverse large";
  }
  return "";
}

int Grader01::getPoints(int test_case)
{
  switch(test_case){
  case 0: return 5;
  case 1: return 5;
  case 2: return 5;
  case 3: return 5;
  case 4: return 5;
  case 5: return 5;
  case 6: return 5;
  case 7: return 5;
  case 8: return 5;
  case 9: return 5;
  case 10: return 5;
  case 11: return 5;
  case 12: return 5;
  case 13: return 5;
  case 14: return 5;
  case 15: return 5;
  case 16: return 5;
  case 17: return 5;
  case 18: return 5;
  case 19: return 5;
  }
  return 0;
}

Date Grader01::getDueDate()
{
  return Date(9, 12, 2013);
}

TestCase * Grader01::grade(int index){
  int single_len2 = 8388607;
  //int single_len2 = 1000;
  int single_len3 = 14348907;
  int single_len_sequence = 4501499;
  int single_len_reverse = 8388607;
  int double_len2 = 65536;
  int double_len3 = 59049;
  int double_len_sequence = 60030;
  int double_len_reverse = 65536;
  switch(index){
  case 0:
    return singleOrderSort2(8);
  case 1:
    return singleOrderSort2(single_len2);
  case 2:
    return singleOrderSort3(12);
  case 3:
    return singleOrderSort3(11);
  case 4:
    return singleOrderSort3(single_len3);
  case 5:
    return singleSequenceOrderSort(14);
  case 6:
    return singleSequenceOrderSort(13);
  case 7:
    return singleSequenceOrderSort(single_len_sequence);
  case 8: 
    return singleReverse(10);
  case 9:
    return singleReverse(single_len_reverse);
  case 10:
    return doubleOrderSort2(8);
  case 11:
    return doubleOrderSort2(double_len2);
  case 12:
    return doubleOrderSort3(12);
  case 13:
    return doubleOrderSort3(11);
  case 14:
    return doubleOrderSort3(double_len3);
  case 15:
    return doubleSequenceOrderSort(14);
  case 16:
    return doubleSequenceOrderSort(13);
  case 17:
    return doubleSequenceOrderSort(double_len_sequence);
  case 18:
    return doubleReverse(10);
  case 19:
    return doubleReverse(double_len_reverse);
  default:
    return NULL;
  }
}
