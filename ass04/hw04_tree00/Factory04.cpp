#include "Factory04.h"
#include "AVLTree.h"

Factory04::Factory04()
{
}

Factory04::~Factory04()
{
}
 
void * Factory04::create(std::string name)
{
  if(name == "IAVLTree"){
    return new AVLTree();
  } else if(name == "IPoint"){
    return NULL;
  } else if(name == "IRTree"){
    return NULL;
  } else if(name == "IBTree"){
    return NULL;
  } else {
    return NULL;
  }
}

extern "C" {

ObjectFactory * createObjectFactory(){
  return new Factory04();  
}

}
