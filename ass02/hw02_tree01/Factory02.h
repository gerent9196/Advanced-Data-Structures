#pragma once

#include "ObjectFactory.h"

class Factory02 : public ObjectFactory {
public:
  Factory02();
  virtual ~Factory02();
  virtual void * create(std::string interface_name);
};
