#include "Factory06.h"
#include "HashMap.h"
#include "HashMap1.h"
#include "BulkHashMap.h"

Factory06::Factory06()
{
}

Factory06::~Factory06()
{
}
 
void * Factory06::create(std::string name)
{
  if(name == "IHashMap1"){
    return new HashMap();
  } else if(name == "IHashMap2"){
    return new HashMap();
  } else if(name == "IHashMap3"){
    return new HashMap1();
  } else if(name == "IHashMap4"){
    return new HashMap1();
  } else if(name == "IBulkHashMap"){
    return new BulkHashMap();
  } else {
    return NULL;
  }
}

extern "C" {

ObjectFactory * createObjectFactory(){
  return new Factory06();  
}

}
