#include <string>
#include <cstring>
#include <vector>
#include <cstdlib>
#include <sstream>
#include <algorithm>
#include <iostream>
#include "Interfaces02.h"
#include "GoldPriorityQueue.h"
#include "TestCase.h"
#include "Stopwatch.h"
#include "Grader02.h"
#include <cmath>
#include "KeyValue.h"

TestCase * Grader02::testWorkload1(int len, int order){

  std::vector<int> input;
  std::vector<int> sorted;
  createVector(input, sorted, order, len, true);

  Stopwatch watch;
  watch.start();

  IPriorityQueue * queue = (IPriorityQueue *) createObject("IPriorityQueue1");
  if(queue == NULL){
    return nullObject("IPriorityQueue1");
  }

  watch.pause();
  GoldPriorityQueue gold_queue(sorted);
  for(size_t i = 0; i < input.size(); ++i){
    int key = input[i];
    std::string value = randomValue();
    gold_queue.push_back(key, value);

    watch.unpause();
    IKeyValue * key_value = (IKeyValue *) createObject("IKeyValue");
    if(key_value == NULL){
      return nullObject("IKeyValue");
    }

    key_value->setKey(key);
    key_value->setValue(value);

    queue->enqueue(key_value);

    int size = queue->size();
    if(size != gold_queue.size()){
     // std::cout << "gold queue:" << gold_queue.size();
      return failed("after enqueue, size is incorrect");
    }

    int user_key = queue->lowestKey();
    IVectorString * user_values = queue->lowestValues();
    gold_queue.iterate();
    int gold_key = gold_queue.lowestKey();
    std::vector<std::string> values = gold_queue.getValues(gold_key);
    watch.pause();        

    if(gold_key != user_key){
      return failed("after enqueue, lowest key is incorrect");
    }

    if(valuesEqual(user_values, values) == false){
      
      return failed("after enqueue, values incorrect");
    }

    bool check_sort = true;
    if(len != 10 && i % 100 != 0){
      check_sort = false;
    }

    if(check_sort){
      watch.unpause();
      IVectorKeyValue * user_sorted = queue->returnSorted();
      watch.pause();
      if(sortedEqual(user_sorted, gold_queue.returnSorted()) == false){
        return failed("after enqueue, sorted is not equal");
      } 
    }
  }

  gold_queue.iterate();
  int count = 0;
  while(gold_queue.hasNext()){
    watch.unpause();
    int user_key = queue->lowestKey();
    IVectorString * user_values = queue->lowestValues();
    watch.pause();    

    int gold_key = gold_queue.lowestKey();
    std::vector<std::string> values = gold_queue.getValues(gold_key);

    if(gold_key != user_key){
      return failed("during dequeue, lowest key is incorrect");
    }

    if(valuesEqual(user_values, values) == false){
      return failed("during dequeue, values incorrect");
    }

    watch.unpause();
    int size = queue->size();
    watch.pause();    
    if(size != gold_queue.size()){
      return failed("during dequeue, size is incorrect");
    }

    bool check_sort = true;
    if(len != 10 && count % 100 != 0){
      check_sort = false;
    }

    if(check_sort){
      IVectorKeyValue * user_sorted = queue->returnSorted();
      std::vector<std::pair<int, std::string> > gold_sorted = gold_queue.returnSorted();
      if(sortedEqual(user_sorted, gold_sorted) == false){
        return failed("during dequeue, sorted is not equal");
      } 
    }
  
    watch.unpause();
    queue->dequeue();
    watch.pause();    
    gold_queue.dequeue();
    ++count;
  }
 
  return passed(watch.getTime());
}

TestCase * Grader02::testWorkload2(int len, int order){
  std::vector<int> input;
  std::vector<int> sorted;
  createVector(input, sorted, order, len, true);

  Stopwatch watch;
  watch.start();

  IPriorityQueue * queue = (IPriorityQueue *) createObject("IPriorityQueue2");
  if(queue == NULL){
    return nullObject("IPriorityQueue2");
  }

  watch.pause();
  GoldPriorityQueue gold_queue(sorted);
  for(size_t i = 0; i < input.size(); ++i){
    int key = input[i];
    std::string value = randomValue();
    gold_queue.push_back(key, value);

    watch.unpause();
    IKeyValue * key_value = (IKeyValue *) createObject("IKeyValue");
    if(key_value == NULL){
      return nullObject("IKeyValue");
    }

    key_value->setKey(key);
    key_value->setValue(value);

    queue->enqueue(key_value);

    int size = queue->size();
    //cout<< "Grader size: " << gold_queue.size() << " My size:"<< queue->size();
    if(size != gold_queue.size()){
      return failed("after enqueue, size is incorrect");
    }

    int user_key = queue->lowestKey();
    IVectorString * user_values = queue->lowestValues();
    gold_queue.iterate();
    int gold_key = gold_queue.lowestKey();
    std::vector<std::string> values = gold_queue.getValues(gold_key);
    watch.pause();        

    if(gold_key != user_key){
      return failed("after enqueue, lowest key is incorrect");
    }

    if(valuesEqual(user_values, values) == false){
      return failed("after enqueue, values incorrect");
    }
  }

  gold_queue.iterate();
  int count = 0;
  while(gold_queue.hasNext()){
    watch.unpause();
    int user_key = queue->lowestKey();
    IVectorString * user_values = queue->lowestValues();
    watch.pause();    

    int gold_key = gold_queue.lowestKey();
    std::vector<std::string> values = gold_queue.getValues(gold_key);

    if(gold_key != user_key){
      return failed("during dequeue, lowest key is incorrect");
    }

    if(valuesEqual(user_values, values) == false){
      return failed("during dequeue, values incorrect");
    }

    watch.unpause();
    int size = queue->size();
    watch.pause();    
    if(size != gold_queue.size()){
      return failed("during dequeue, size is incorrect");
    }

    watch.unpause();
    queue->dequeue();
    watch.pause();    
    gold_queue.dequeue();
    ++count;
  }
 
  return passed(watch.getTime());
}

TestCase * Grader02::testWorkload3(int len, int order, int merge_count,
    int merge_len){

  std::vector<int> input;
  std::vector<int> sorted;
  createVector(input, sorted, order, len, false);

  Stopwatch watch;
  watch.start();


  
  IPriorityQueue * queue = (IPriorityQueue *) createObject("IPriorityQueue3");
  if(queue == NULL){
    return nullObject("IPriorityQueue3");
  }

  watch.pause();
  GoldPriorityQueue gold_queue(sorted);

  for(size_t i = 0; i < merge_len; ++i){
    int key = input[i];
    std::string value = randomValue();
    gold_queue.push_back(key, value);

    watch.unpause();
    IKeyValue * key_value = (IKeyValue *) createObject("IKeyValue");
    if(key_value == NULL){
      return nullObject("IKeyValue");
    }

    key_value->setKey(key);
    key_value->setValue(value);

    queue->enqueue(key_value);

    int size = queue->size();
    if(size != gold_queue.size()){
      return failed("after enqueue, size is incorrect");
    }

    int user_key = queue->lowestKey();
    IVectorString * user_values = queue->lowestValues();
    gold_queue.iterate();
    int gold_key = gold_queue.lowestKey();
    std::vector<std::string> values = gold_queue.getValues(gold_key);
    watch.pause();        
/*
    if(gold_key != user_key){
      return failed("after enqueue, lowest key is incorrect");
    }

    if(valuesEqual(user_values, values) == false){
      return failed("after enqueue, values incorrect");
    }
    */
  }

  for(int i = 1; i < merge_count; ++i){
    watch.unpause();
    IPriorityQueue * queue2 = (IPriorityQueue *) createObject("IPriorityQueue3");
    if(queue == NULL){
      return nullObject("IPriorityQueue3");
    }

    watch.pause();

    for(int j = (i * merge_len); j < ((i + 1) * merge_len); ++j){
      int key = input[j];
      std::string value = randomValue();
      gold_queue.push_back(key, value);

      watch.unpause();
      IKeyValue * key_value = (IKeyValue *) createObject("IKeyValue");
      if(key_value == NULL){
        return nullObject("IKeyValue");
      }

      key_value->setKey(key);
      key_value->setValue(value);

      queue2->enqueue(key_value);
      watch.pause();
    }
    
    watch.unpause();
    queue->merge(queue2);
    watch.pause();
  }

  gold_queue.iterate();

  int count = 0;
  while(gold_queue.hasNext()){
    watch.unpause();
    int user_key = queue->lowestKey();
    IVectorString * user_values = queue->lowestValues();
    watch.pause();    

    int gold_key = gold_queue.lowestKey();
    std::vector<std::string> values = gold_queue.getValues(gold_key);

    if(gold_key != user_key){
      return failed("during dequeue, lowest key is incorrect");
    }

    if(valuesEqual(user_values, values) == false){
      return failed("during dequeue, values incorrect");
    }

    watch.unpause();
    int size = queue->size();
    watch.pause();    
    if(size != gold_queue.size()){
      return failed("during dequeue, size is incorrect");
    }

    watch.unpause();
    queue->dequeue();
    watch.pause();    
    gold_queue.dequeue();
    ++count;
  }
 
  return passed(watch.getTime());
}

TestCase * Grader02::testWorkload4(int len, int order, int merge_count,
    int merge_len){

  std::vector<int> input;
  std::vector<int> sorted;
  createVector(input, sorted, order, len, false);

  Stopwatch watch;
  watch.start();

  IPriorityQueue * queue = (IPriorityQueue *) createObject("IPriorityQueue4");
  if(queue == NULL){
    return nullObject("IPriorityQueue4");
  }

  watch.pause();
  GoldPriorityQueue gold_queue(sorted);

  for(size_t i = 0; i < merge_len; ++i){
    int key = input[i];
    std::string value = randomValue();
    gold_queue.push_back(key, value);

    watch.unpause();
    IKeyValue * key_value = (IKeyValue *) createObject("IKeyValue");
    if(key_value == NULL){
      return nullObject("IKeyValue");
    }

    key_value->setKey(key);
    key_value->setValue(value);

    queue->enqueue(key_value);

    int size = queue->size();
    if(size != gold_queue.size()){
      return failed("after enqueue, size is incorrect");
    }

    int user_key = queue->lowestKey();
    IVectorString * user_values = queue->lowestValues();
    gold_queue.iterate();
    int gold_key = gold_queue.lowestKey();
    std::vector<std::string> values = gold_queue.getValues(gold_key);
    watch.pause();        

    if(gold_key != user_key){
      return failed("after enqueue, lowest key is incorrect");
    }

    if(valuesEqual(user_values, values) == false){
      return failed("after enqueue, values incorrect");
    }
  }

  for(int i = 1; i < merge_count; ++i){
    watch.unpause();
    IPriorityQueue * queue2 = (IPriorityQueue *) createObject("IPriorityQueue4");
    if(queue == NULL){
      return nullObject("IPriorityQueue4");
    }

    watch.pause();

    for(int j = (i * merge_len); j < ((i + 1) * merge_len); ++j){
      int key = input[j];
      std::string value = randomValue();
      gold_queue.push_back(key, value);

      watch.unpause();
      IKeyValue * key_value = (IKeyValue *) createObject("IKeyValue");
      if(key_value == NULL){
        return nullObject("IKeyValue");
      }

      key_value->setKey(key);
      key_value->setValue(value);

      queue2->enqueue(key_value);
      watch.pause();
    }
    
    watch.unpause();
    queue->merge(queue2);
    watch.pause();

    gold_queue.iterate();

    watch.unpause();
    int user_key = queue->lowestKey();
    IVectorString * user_values = queue->lowestValues();
    watch.pause();    

    int gold_key = gold_queue.lowestKey();
    std::vector<std::string> values = gold_queue.getValues(gold_key);

    if(gold_key != user_key){
     // cout << "gold key:" << gold_key << " "<< user_key;
      return failed("during dequeue, lowest key is incorrect");
    }


    if(valuesEqual(user_values, values) == false){
      return failed("during dequeue, values incorrect");
    }
  }

  return passed(watch.getTime());
}

int Grader02::size(){
  return 24;
}

std::string Grader02::getDescription(int test_case)
{
  switch(test_case){
  case 0: return "workload1 small ascending";
  case 1: return "workload1 small descending";
  case 2: return "workload1 small random";
  case 3: return "workload1 large ascending";
  case 4: return "workload1 large descending";
  case 5: return "workload1 large random";
  case 6: return "workload2 small ascending";
  case 7: return "workload2 small descending";
  case 8: return "workload2 small random";
  case 9: return "workload2 large ascending";
  case 10: return "workload2 large descending";
  case 11: return "workload2 large random";
  case 12: return "workload3 small ascending";
  case 13: return "workload3 small descending";
  case 14: return "workload3 small random";
  case 15: return "workload3 large ascending";
  case 16: return "workload3 large descending";
  case 17: return "workload3 large random";
  case 18: return "workload4 small ascending";
  case 19: return "workload4 small descending";
  case 20: return "workload4 small random";
  case 21: return "workload4 large ascending";
  case 22: return "workload4 large descending";
  case 23: return "workload4 large random";
  }
  return "";
}

int Grader02::getPoints(int test_case)
{
  switch(test_case){
  case 0: return 4;
  case 1: return 4;
  case 2: return 4;
  case 3: return 4;
  case 4: return 4;
  case 5: return 4;
  case 6: return 4;
  case 7: return 4;
  case 8: return 4;
  case 9: return 4;
  case 10: return 4;
  case 11: return 4;
  case 12: return 4;
  case 13: return 4;
  case 14: return 4;
  case 15: return 4;
  case 16: return 4;
  case 17: return 5;
  case 18: return 4;
  case 19: return 4;
  case 20: return 4;
  case 21: return 5;
  case 22: return 5;
  case 23: return 5;
  }
  return 0;
}

Date Grader02::getDueDate()
{
  return Date(9, 26, 2013);
}
  
TestCase * Grader02::grade(int index){
  switch(index){
  case 0:
    return testWorkload1(10, 0);
  case 1:
    return testWorkload1(10, 1);
  case 2:
    return testWorkload1(10, 2);
  case 3:
    return testWorkload1(20000, 0);
  case 4:
    return testWorkload1(20000, 1);
  case 5:
    return testWorkload1(20000, 2);
  case 6:
    return testWorkload2(10, 0);
  case 7:
    return testWorkload2(10, 1);
  case 8:
    return testWorkload2(10, 2);
  case 9:
    return testWorkload2(50, 0);
  case 10:
    return testWorkload2(50000, 1);
  case 11:
    return testWorkload2(50000, 2);
  case 12:
    return testWorkload3(50000, 0, 5, 10);
  case 13:
    return testWorkload3(50, 1, 5, 10);
  case 14:
    return testWorkload3(50, 2, 5, 10);
  case 15:
    return testWorkload3(50000, 0, 100, 500);
  case 16:
    return testWorkload3(50000, 1, 100, 500);
  case 17:
    return testWorkload3(50000, 2, 100, 500);
  case 18:
    return testWorkload4(50, 0, 5, 10);
  case 19:
    return testWorkload4(50, 1, 5, 10);
  case 20:
    return testWorkload4(50, 2, 5, 10);
  case 21:
    return testWorkload4(500000, 0, 5000, 100);
  case 22:
    return testWorkload4(500000, 1, 5000, 100);
  case 23:
    return testWorkload4(500000, 2, 5000, 100);
  default:
    return NULL;
  }
}
