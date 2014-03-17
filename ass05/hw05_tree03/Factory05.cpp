#include "Factory05.h"
#include "Sequencer.h"

Factory05::Factory05()
{
}

Factory05::~Factory05()
{
}
 
void * Factory05::create(std::string name)
{
  if(name == "ISequencer"){
    return new Sequencer();
  } else {
    return NULL;
  }
}

extern "C" {

ObjectFactory * createObjectFactory(){
  return new Factory05();  
}

}
