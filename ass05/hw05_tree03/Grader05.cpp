#include <string>
#include <cstring>
#include <cstdlib>
#include <sstream>
#include <algorithm>
#include <iostream>
#include <set>
#include "Interfaces05.h"
#include "TestCase.h"
#include "Stopwatch.h"
#include "Grader05.h"
#include <cmath>
#include <fstream>
#include "Commands05.h" 

TestCase * Grader05::testBuildGraph(std::string reads_filename, std::string results_filename)
{
  Commands05 cmds05;
  std::vector<std::string> reads;
  cmds05.readReads(reads_filename, reads);

  if(reads.size() == 0){
    return failed("cannot load input file");
  }

  CommandsGraph results;
  cmds05.readBuildGraphResults(results_filename, results);

  if(results.vertices.size() == 0){
    return failed("cannot load input file");
  }

  Stopwatch watch;
  watch.start();

  ISequencer * sequencer = (ISequencer *) createObject("ISequencer");
  if(sequencer == NULL){
    return nullObject("sequencer");
  }

  IGraph * graph = sequencer->buildGraph(reads);
  if(graph == NULL){
    return nullObject("IGraph");
  }

  std::vector<IVertex *> product_vertices = graph->getVertices();
  if(product_vertices.size() != results.vertices.size()){
    return failed("vertices count does not match");
  }

  std::set<std::string> visited_vertices;

  for(int k = 0; k < product_vertices.size(); ++k){
    IVertex * product_vertex = product_vertices[k];
    std::string name = product_vertex->getName();
    if(results.vertices.find(name) == results.vertices.end()){
      return failed(std::string("cannot find matching vertex for: ")+name);
    }
    std::string gold_name = name;
    visited_vertices.insert(name);

    std::map<std::string, int> gold_edges = results.edges[gold_name];
    std::vector<IEdge *> product_edges = product_vertex->getEdges();
    if(gold_edges.size() != product_edges.size()){
      return failed("edges count does not match");
    }
    std::map<std::string, IEdge *> product_edges_map;
    for(size_t i = 0; i < product_edges.size(); ++i){
      IEdge * product_edge = product_edges[i];
      product_edges_map[product_edge->getTarget()->getName()] = product_edge;
    }
    std::map<std::string, int>::iterator iter = gold_edges.begin();
    while(iter != gold_edges.end()){
      std::string gold_target = iter->first;
      int gold_weight = iter->second;
      if(product_edges_map.find(gold_target) == product_edges_map.end()){
        return failed("cannot find corresponding edge");
      }
      IEdge * product_edge = product_edges_map[gold_target]; 
      //std::cout << product_vertex->getName() << " " << gold_target << " " << gold_weight << " " << product_edge->getWeight() << std::endl;
      if(gold_weight != product_edge->getWeight()){
        return failed("weight does not match for corresponding edges");
      }
      ++iter;
    }
  }

  if(visited_vertices.size() != results.vertices.size()){
    return failed("duplicate vertices");
  }

  watch.stop();

  return passed(watch.getTime());
}

void Grader05::print(std::vector<std::string>& vec)
{
  std::cout << "[";
  for(size_t i = 0; i < vec.size(); ++i){
    std::cout << vec[i];
    if(i < vec.size() - 1){
      std::cout << ",";
    }
  }
  std::cout << "]" << std::endl;
}

TestCase * Grader05::testTSP(std::string reads_filename, std::string start_read, std::string results_filename)
{  
  Commands05 cmds05;
  std::vector<std::string> reads;
  cmds05.readReads(reads_filename, reads);

  if(reads.size() == 0){
    return failed("cannot load input file #1");
  }

  std::vector<std::string> results;
  cmds05.readReads(results_filename, results);

  if(results.size() == 0){
    return failed("cannot load input file #2");
  }

  Stopwatch watch;
  watch.start();

  ISequencer * sequencer = (ISequencer *) createObject("ISequencer");
  if(sequencer == NULL){
    return nullObject("sequencer");
  }

  IGraph * graph = sequencer->buildGraph(reads);
  if(graph == NULL){
    return nullObject("IGraph");
  }

  std::vector<std::string> product_results = sequencer->tsp(start_read, graph);
  watch.stop();

  if(results.size() != product_results.size()){
    return failed("travelling salesman size result does not match");
  }

  for(size_t i = 0; i < results.size(); ++i){
    std::string gold_result = results[i];
    std::string product_result = product_results[i];
    if(gold_result != product_result){
      return failed("item on path does not match");
    }
  }

  return passed(watch.getTime());
}

TestCase * Grader05::testAssemble(std::string reads_filename, std::string result)
{
  Commands05 cmds05;
  std::vector<std::string> reads;
  cmds05.readReads(reads_filename, reads);

  if(reads.size() == 0){
    return failed("cannot load input file");
  }

  reads.pop_back();

  Stopwatch watch;
  watch.start();

  ISequencer * sequencer = (ISequencer *) createObject("ISequencer");
  if(sequencer == NULL){
    return nullObject("sequencer");
  }

  std::string product_result = sequencer->assemble(reads);
  watch.stop();

  if(product_result != result){
    std::cout << "product_size: " << product_result.size() << std::endl;
    std::cout << "result_size:  " << result.size() << std::endl;
    for(int i = 0; i < product_result.size(); ++i){
      char lhs = product_result[i];
      char rhs = result[i];
      if(lhs != rhs){
        std::cout << "mismatch at: " << i << std::endl;
        std::string snip_product;
        std::string snip_result;
        for(int j = i - 20; j < i + 20; ++j){
          snip_product += product_result[j];
          snip_result += result[j];
        }
        std::cout << "snip_product: " << snip_product << std::endl;
        std::cout << "snip_result:  " << snip_result << std::endl;
        break;
      }
    }
    return failed("assemble incorrect");
  }

  return passed(watch.getTime());
}

int Grader05::size(){
  return 8;
}

std::string Grader05::getDescription(int test_case)
{
  switch(test_case){
  case 0: return "Sequencer Build Graph Small";
  case 1: return "Sequencer Travelling Salesman Problem Small";
  case 2: return "Sequencer Assemble Small";
  case 3: return "Sequencer Build Graph Medium";
  case 4: return "Sequencer Travelling Salesman Problem Medium";
  case 5: return "Sequencer Assemble Medium";
  case 6: return "Sequencer Build Graph Large";
  case 7: return "Sequencer Assemble Large";
  }
  return "";
}

int Grader05::getPoints(int test_case)
{
  switch(test_case){
  case 0: return 12;
  case 1: return 12;
  case 2: return 12;
  case 3: return 12;
  case 4: return 13;
  case 5: return 13;
  case 6: return 13;
  case 7: return 13;
  }
  return 0;
}

Date Grader05::getDueDate()
{
  return Date(11, 21, 2013);
}
  
TestCase * Grader05::grade(int index){
  switch(index){
  case 0:
    return testBuildGraph("reads_short.txt", "graph_result_1.bin");
  case 1:
    return testTSP("reads_short.txt", "ggccggttgc", "tsp_result_1.bin");
  case 2:
    return testAssemble("tsp_result_1.bin", "ggccggttgcttgatccac");
  case 3:
    return testBuildGraph("reads_medium.txt", "graph_result_2.bin");
  case 4:
    return testTSP("reads_medium.txt", "ggccggttgc", "tsp_result_2.bin");
  case 5:
    return testAssemble("tsp_result_2.bin", "ggccggttgcttgatccaccaggaaccgt");
  case 6:
    return testBuildGraph("reads_long1.txt", "graph_result_3.bin");
  case 7:
    return testAssemble("reads_long2.txt", "ggccggttgcttgatccaccaggaaccgtctgttagcaccgccgaacgcctcgttttccccctgctcctgcacgtttgagtcccgcgtgaacgccctcgcccaagccgctacccccctcccaagtgctggaattctctgggctcggatgctggatgccatccgccaggagaagttcgactacgcgctgagatggctggagcggatgcgcccgctggaggtgcgtgacggtgccctggtgatgggcgttccggaccgcttcttccgcgactgggtggatgaccactaccgccccatgctggatgtccagctcgcacggatgggggagggcctgacctccatcgcctatgaggtagtggagggcctggagccggacccgcattttccacccacaccctcagtcaaggcgagcgccacgcgtccgggccggctgaacgcgcttcaccttcgacaccttcgtggtggcggacagcaaccagctcccggccgccgcggcgcaggccgtggccgacaagccgggccaccactacaacccgctctacatctacggcggcacgggtctgggcaagacgcacctgctccaggcagtgggcaacctcatctgggagcgagatccatcccagcgcgtggtgttcctctccagcgagcagttcaccaacgagtacgtggagagcgtccgcgagcaccgcatgggggacttccgccggaagttccgtgaggagtgcgacgtgctcctcctcgacgacatccagttcctcggcaagcgtgaggagacgcagaaggagttcttctacaccttcaacacgctctacgagatgaacaaggccatcgtcctcaccagcgacaccgtgcccgcggagattccgggcctggaggaccggctgcgcagccgcttcgccatggggctgatgacggacatccgcgagcccacctacgagacgcgggtggccatcctccagaagaaggccgtggccgaaggtctggacctgccggactcggtggcgcacttcatcgccaagcacatccagaagaacgtgcgcgagttggaaggcgcgctggtgaagctgtccgcggtgcacagcctgacgcgccagcccgtgacggaggacttcgcgtcccaggtgctgcgcgacatcctcccgcccacagcgcggtggacgtggaggccatccagcgcgaggtggcccgcttctacaaagtcacggtggagtcgctgaaggaagaccgccggcacaaggccctggcccatgcgcgccaggtggccatgtacctcagccgcaagctgacgaagagctccttcccggaaatcgccgcgcgcttcagcaaggaccactccaccgtcatctccgcggttcgcaaggtggaaggcctccgcgtgacggatgccaccgtgcagcgtgagttggcggagctggaattgaagctcggcaatccctgaaacagccgtacctttgtttcatgtcggacgacacgcgcccgcgtgaaacgggccgtgtccggctgacgcgcaaccaggattgacgctcgggcgcgtatgcgggggagtgagcccgcgcctgaagagcctggtccttctgctcgccgtgctcacggcagccgcgctgtggcgtgcgggccaggagacacagacgccggcttctcctgagacaccgccggctgtctcaccgtccttggatgatgaagccctcacaccggctcccgaggaaaaccttccaggcgtgaaggggcgggagcgggtgctcgtcgtgggccaccggcttcgttacacgttcgacctggacctccggacccacacggagaatcgggccggcgcgcgcgagtccctgcacaccggatggagcggcctgttcgagctcacctacctgggcgcggagggtgaacagcacctgttctccggccacctcgtgcccacgcgggtggccgtggaatccggtgagacgctggcgcccggtgacgcagcgatgcaggcgctccggggcatgttcgagcggccggtgtacgtgggccaggacgtgcggggccgggtgatggccgtgcacttcgatgcggcgcaggacgcgacggcgcggcggctcgtgcgcctgctgctcgcgtcgacgcagttcgtggcggaggacggcccccgctggagcaccgaggagccggactcgcgcggtgacctcgaagccgtgtaccgcgcgggtggcagcgcgaacacctacgtgaagacgaagcggcgctacctgcgcgctggctcggcggtgcttccacggctgcaagggcacctggacttcaccctgttcgcggatgggcacgtgaaggaagcgacgggctcggacgtggtggagttgggcggaggcagcacggggctccctcgcatccgcgaggaggcgagggtcgcgttgaccaacgtgggcgtggactaccggctttcgtcgctgaggccgtttgaggccacgcggacgacgttgcggtcggagcggctcacggattcggccgacatggagggggcttcgctggaggcgcgggacaggcagctcgtgaagggggtgaagctggatgacttgctgcgggcactggcgaagcgcgaggacctggacaccgcgcggctgcgactgacggccttgttccgacagaatctggcggaagtggaacgagccgtggcgctgattcgtcagggctccgcggacgcggtgcgctccgagcagatactggaggcgctggccagcgcggggacgccagaggcgcagcgggcgctggtgtccgtgttggagggagaacgggtccggccgaagacccgggcccacgcggcacgggcagcgggacggatggaacggccttcgctgctgctcggtgatgcactggagcgcgtgatggatgggacgcgggacgcgggggtgaggaacgcggcggcgctgtcgatgggggcgctgtcgaagacgttggaggtggcggagccgggccggagccaggcgctggtggagggaatcgtgaggcgctgccgcacgggtgctttggagcccgaggtctgtctggatgccctggcccgggcaggtgctccggtgggattggcctacgtgaagtcggcgctcgtgcatccggaggcggatgttcggggcgcggcgacgaaggcactgagtgccattcctggcgcggcggtggatgcattgttggaccaggtgatgctcgacgacccgagcccgcgggttcgtgcgctcgcggtgaaggctgtctctcaacgggtcactggcgcccacttggaagtactggcccgggtgctgcgctccgagcggagtgagcgcgtccgcatcgaagtggtgcggctgctgggccacctgcaagccgtggaggctcccgctgcggccctgcttcgcgatgtggccgcgaacgatgggtccgcgaacgtacgcgcgctggcggcgtcactgctcggcgaatagggcggggtgccgggcggatgagttcacctggcatccgttccacttcgaagcgctacgcgtccttgcggcgacggcccatgacgacccgcatcagtcccgcgagcattcacggaagcagtgcggaaggcacgctcagtgcgcagcggggggaggggcctcggagatgctctccagggtctcgccgacgtcctcctccgccagcgcctccagcaagtcgcccatcgcgacaatccccaccagcttcttgtcccggtcgagcgcgaggatgcggcggaccttcttctccttcatcttctccgccaccacggagatgtcctcgtcatcgaaggcgtattcgagctgccccgtcatcgcctccgccaccgtcgtgctgttggggtcctttccctgggacaccgcacgcaccacgatgtcgcggtcggtgatgatgcccatcagccggtcaccatcacacacgggcagcgggcccacgctcagctcgcgcatcttcaacgcggcgtccttcaatgaatccttcgcgttgatgaccgtgacgtccttcgtcatcacgtcttgtaccttccgcatcacacggctccttccttgggttcaggcctcgggcacccacaacgagcgcaggtctgcggggagctggcccatgacgtcgtcggcctcgccctcgctgatgtgatttcgcaccgtgacgaacacggcccgggccaggcgttcggcctcgttgggcgtggtgtcgagctcctcggccaccatggcgaggaactgctccagcttgtacttccgggcgaccttgccctcgtgccgaggacaccgcttcagcatgtccctcaccttccgcggaagctgggcctccaggtgcttcgcctcggtgtccatgaggcgttgctccagcagacacagcacggactgcgcggccttctccgccaggccacgaacgacgcccgcgttcgcttcgaggtccttcaagaaggccatataggtctgcgccgcgtgcgactcactgcgctgctccttgaggctgggcgtagcgctccggccctccgctgcctctccctgctcctcacgtatgttcgccatgacggtggcctccccggtgtcgggcttgggtctcttccctgagcgtgggcaccccacgttccccaggcaccggccgccccccgcgcgccgggacgccagggcgggaagcgagccaagcaccggcggcaccgtctcgccgccgtcagtccaccgcgccgccgagcagctccaccatccgagtccggtgcaacacgccccagagcgccagcgcgaccaacgccagacacaccgcgccgagcgcctcccaccgccggccaatgggcggccgtgcctccgggtccacccgccgcagcgccaccaggcccaggatgagggcgagcatggacaaccccgcgaagacgaatgtcagcgcgctccacaccccgaagtaggagagcagcggcgcgaacacgggcaggaacagcgaccccacgctcagcgacagcgcatgccgagcaagggggttgttgacccgcaggtcccatagctggcgtagctcgcgctcggggacatccaggcggaa");
  default:
    return NULL;
  }
}
