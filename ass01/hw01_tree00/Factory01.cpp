#include "Factory01.h"
#include "SingleNode.h"
#include "SingleList.h"
#include "DoubleNode.h"
#include "DoubleList.h"

Factory01::Factory01()
{
}

Factory01::~Factory01()
{
}
 
void * Factory01::create(std::string name)
{
  if(name == "ISingleNode"){
    return new SingleNode();
  } else if(name == "ISingleList"){
    return new SingleList();
  } else if(name == "IDoubleNode"){
    return new DoubleNode();
  } else if(name == "IDoubleList"){
    return new DoubleList();
  } else {
    return NULL;
  }
}

extern "C" {

ObjectFactory * createObjectFactory(){
  return new Factory01();  
}

}
