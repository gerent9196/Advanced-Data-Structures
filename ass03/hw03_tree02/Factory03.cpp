#include "Factory03.h"
#include "VectorDoubleSort.h"
#include "SmoothSort.h"
#include "RunningMedian.h"
#include "LinkedListSort.h"
#include "RecordsSearch.h"
Factory03::Factory03()
{
}

Factory03::~Factory03()
{
}
 
void * Factory03::create(std::string name)
{
  if(name == "IVectorDoubleSort1"){
    return new VectorDoubleSort();
  } else if(name == "IVectorDoubleSort2"){
    return new VectorDoubleSort();
  } else if(name == "ISmoothSort"){
    return new SmoothSort();
  } else if(name == "ILinkedListSort"){
    return new LinkedListSort();
  } else if(name == "IRunningMedian"){
    return new RunningMedian();
  } else if(name == "IRecordsSearch"){
    return new RecordsSearch();
  } else {
    return NULL;
  }
}

extern "C" {

ObjectFactory * createObjectFactory(){
  return new Factory03();  
}

}
