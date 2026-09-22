#include <Arduino.h>
#include "validate.h"
#include "constants.h"
#include "settings.h"

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
  int code = Settings::getErrorStatus();
  if (code > 0)
    return code;
  // 1 - closing, 2 - break, 3 - burner is broken
  bool errorOverheat = false;
  bool errorUnderheat = false;

  // overheat temperature
  if (temperature >= MAX_PERMITTED_TEMP)
  {
    errorOverheat = true;
  }
  else if (temperature <= MAX_PERMITTED_TEMP - DEFAULT_HYSTERESIS)
  {
    errorOverheat = false;
  }

  // low temperature
  if (temperature <= MIN_PERMITTED_TEMP)
  {
    errorUnderheat = true;
  }
  else if (temperature >= MIN_PERMITTED_TEMP + DEFAULT_HYSTERESIS)
  {
    errorUnderheat = false;
  }

  if (errorOverheat)
    code = 1;

  if (errorUnderheat)
    code = 2;

  if (code > 0)
    setErrorCodeAndStatus(code);

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