#pragma once

#include "ObjectFactory.h"

class Factory07 : public ObjectFactory {
public:
  Factory07();
  virtual ~Factory07();
  virtual void * create(std::string interface_name);
};
