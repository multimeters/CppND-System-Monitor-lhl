#ifndef PROCESSOR_H
#define PROCESSOR_H
#include "linux_parser.h"
class Processor {
 public:
  float Utilization();  // TODO: See src/processor.cpp
  void setUtil(float u) { util_ = u; }
  // TODO: Declare any necessary private members
 private:
  float util_;
};

#endif