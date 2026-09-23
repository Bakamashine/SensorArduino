#pragma once
#include "error.h"

class Validate : public Error
{
private:
  float temperature = 0.0F;
  static unsigned long mil;

public:
  Validate &setTemperature(float);
  int executePipelineValidate();
};
