#include <string>
#include <cstring>
#include <cstdlib>
#include <sstream>
#include <algorithm>
#include <iostream>
#include <set>
#include "Commands07.h"
#include "Interfaces07.h"
#include "TestCase.h"
#include "Stopwatch.h"
#include <cmath>
#include <fstream>
#include "Grader07.h"

TestCase * Grader07::testStringSearch(std::string cmds_filename, std::string input_filename)
{
  std::vector<StringSearchCmd> commands;

  Commands07 cmds07;
  cmds07.loadStringSearchCommmands(cmds_filename, commands);
  std::string to_search = cmds07.readStringFile(input_filename);

  if(commands.size() == 0){
    return failed("cannot read input file #1");
  }

  if(to_search == ""){
    return failed("cannot read input file #2");
  }

  Stopwatch watch;
  watch.start();

  IStringSearch * searcher = (IStringSearch *) createObject("IStringSearch");
  if(searcher == NULL){
    return nullObject("IStringSearch");
  }

  watch.pause();
  searcher->prepareText(to_search);
  watch.unpause();

  for(size_t i = 0; i < commands.size(); ++i){
    StringSearchCmd cmd = commands[i];
    std::vector<int> product_results = searcher->search(cmd.to_find);
    if(product_results.size() != cmd.positions.size()){
      return failed("incorrect return size");
    }
    std::sort(product_results.begin(), product_results.end());
    if(product_results != cmd.positions){
      return failed("at least one incorrect return index");
    }
  }

  watch.stop();
  return passed(watch.getTime());
}

TestCase * Grader07::testStringSort(std::string input_filename)
{
  std::vector<std::string> input;
  std::vector<std::string> output;

  Commands07 cmds07;
  cmds07.readReads(input_filename, input);
  cmds07.readReads(input_filename, output);

  if(input.size() == 0){
    return failed("cannot read input file #1");
  }  
  
  if(output.size() == 0){
    return failed("cannot read input file #2");
  }  

  Stopwatch watch;
  watch.start();

  IStringSort * sorter = (IStringSort *) createObject("IStringSort");
  if(sorter == NULL){
    return nullObject("IStringSort");
  }

  sorter->sort(input);
  watch.stop();
  
  std::sort(output.begin(), output.end());

  if(input.size() != output.size()){
    return failed("incorrect size");
  }
  if(input != output){
    return failed("at least one incorrect string");
  }

  return passed(watch.getTime());
}

TestCase * Grader07::testSpellCheck(std::string filename)
{
  Commands07 cmds07;
  std::vector<std::string> words;
  std::vector<SpellCheckCmd> commands;

  cmds07.readReads("words", words);
  cmds07.loadSpellCheckCommands(filename, commands);

  if(words.size() == 0){
    return failed("cannot read input file #1");
  }

  if(commands.size() == 0){
    return failed("cannot read input file #2");
  }

  Stopwatch watch;
  watch.start();

  ISpellCheck * checker = (ISpellCheck *) createObject("ISpellCheck");
  if(checker == NULL){
    return nullObject("ISpellCheck");
  }

  watch.pause();
  checker->loadDictionary(words);
  watch.unpause();

  for(size_t i = 0; i < commands.size(); ++i){
    SpellCheckCmd cmd = commands[i];
    std::vector<std::string> product_corrections = checker->suggestCorrections(cmd.word);
    watch.pause();
    std::sort(product_corrections.begin(), product_corrections.end());
    if(product_corrections != cmd.corrections){
      return failed("corrections mismatch");
    }
    watch.unpause();
  }

  watch.stop();
  return passed(watch.getTime());
}

TestCase * Grader07::testCompress(std::string input_filename, std::string output_filename)
{
  Commands07 cmds07;
  std::string input = cmds07.readStringFile(input_filename);

  Stopwatch watch;
  watch.start();

  ICompress * compressor = (ICompress *) createObject("ICompress");
  if(compressor == NULL){
    return nullObject("ICompress");
  }

  std::string output = compressor->compress(input);
  watch.stop();

  cmds07.writeStringFile(output_filename, output);
  return passed(watch.getTime()+output.size());
}

TestCase * Grader07::testDecompress(std::string input_filename, std::string output_filename)
{
  Commands07 cmds07;
  std::string input = cmds07.readStringFile(input_filename);
  std::string gold_output = cmds07.readStringFile(output_filename);
  
  Stopwatch watch;
  watch.start();

  ICompress * compressor = (ICompress *) createObject("ICompress");
  if(compressor == NULL){
    return nullObject("ICompress");
  }

  std::string output = compressor->decompress(input);
  watch.stop();

  if(gold_output != output){
    return failed("results do not match");
  }

  return passed(watch.getTime());
}

int Grader07::size(){
  return 10;
}

std::string Grader07::getDescription(int test_case)
{
  switch(test_case){
  case 0: return "String Search Small";
  case 1: return "String Search Large";
  case 2: return "String Sort Small";
  case 3: return "String Sort Large";
  case 4: return "Spell Check Small";
  case 5: return "Spell Check Large";
  case 6: return "Compress Small";
  case 7: return "Decompress Small";
  case 8: return "Compress Large";
  case 9: return "Decompress Large";
  }
  return "";
}

int Grader07::getPoints(int test_case)
{
  switch(test_case){
  case 0: return 2;
  case 1: return 2;
  case 2: return 2;
  case 3: return 2;
  case 4: return 2;
  case 5: return 2;
  case 6: return 2;
  case 7: return 2;
  case 8: return 2;
  case 9: return 2;
  }
  return 0;
}

Date Grader07::getDueDate()
{
  return Date(12, 5, 2013);
}
  
TestCase * Grader07::grade(int index){
  switch(index){
  case 0:
    return testStringSearch("string_search_1.bin", "sequence_small.txt");
  case 1:
    return testStringSearch("string_search_2.bin", "sequence_large.txt");
  case 2:
    return testStringSort("string_sort_input_1.txt");
  case 3:
    return testStringSort("string_sort_input_2.txt");
  case 4:
    return testSpellCheck("spell_check_1.bin");
  case 5:
    return testSpellCheck("spell_check_2.bin");
  case 6:
    return testCompress("sequence_small.txt", "compress_output.bin");
  case 7:
    return testDecompress("compress_output.bin", "sequence_small.txt");
  case 8:
    return testCompress("sequence_medium.txt", "compress_output.bin");
  case 9:
    return testDecompress("compress_output.bin", "sequence_medium.txt");
  default:
    return NULL;
  }
}
