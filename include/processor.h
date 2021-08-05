#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <vector>
#include <string>
#include "linux_parser.h"

class Processor {
 public:
  double Utilization();  // TODO: See src/processor.cpp
  // TODO: Declare any necessary private members
 private:
   float totalCpuTime_;
   std::vector<long> convertToFloat();
};

#endif