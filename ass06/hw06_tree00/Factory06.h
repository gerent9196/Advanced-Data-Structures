#pragma once

#include "ObjectFactory.h"

class Factory06 : public ObjectFactory {
public:
  Factory06();
  virtual ~Factory06();
  virtual void * create(std::string interface_name);
};
