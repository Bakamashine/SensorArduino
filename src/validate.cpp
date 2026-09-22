#include <Arduino.h>
#include "validate.h"
#include "constants.h"

Validate &Validate::setTemperature(float temp)
{
  temperature = temp;
  return *this;
}

float Validate::getTemperature()
{
  return temperature;
}

unsigned long Validate::mil = 0;

int Validate::executePipelineValidate()
{
  int code = 0;
  // 1 - closing, 2 - break, 3 - burner is broken
  if (temperature >= MAX_PERMITTED_TEMP - DEFAULT_DELTA)
  {
    code = 1;
    setErrorCodeAndStatus(code);
  }
  else if (temperature <= MIN_PERMITTED_TEMP + DEFAULT_DELTA)
  {
    code = 2;
    setErrorCodeAndStatus(code);
  }

  if (code > 0)
  {
    if (mil == 0)
      mil = millis();
    if (millis() - mil >= ERROR_PERIOD)
    {
      code = 3;
      setErrorCodeAndStatus(code);
    }
  }
  else
  {
    mil = 0;
  }
  return code;
}