#include "Factory07.h"
#include "StringSearch.h"
#include "StringSort.h"
#include "SpellCheck.h"
#include "Compress.h"
Factory07::Factory07()
{
}

Factory07::~Factory07()
{
}
 
void * Factory07::create(std::string name)
{
  if(name == "IStringSearch"){
    return new StringSearch();
  } else if(name == "IStringSort"){
    return new StringSort();
  } else if(name == "ISpellCheck"){
    return new SpellCheck();
  } else if(name == "ICompress"){
    return new Compress();
  } else {
    return NULL;
  }
}

extern "C" {

ObjectFactory * createObjectFactory(){
  return new Factory07();  
}

}
