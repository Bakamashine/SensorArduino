#include <Arduino.h>
#include "temperature.h"
#include "settings.h"
#include "helper.h"

#define BREAK 0
#define MIN_V 0.5F
#define MIN_T -10
#define MAX_V 4.5F
#define MAX_T 110

#define ATTEMPTS 5

Temperature::Temperature()
{
  tick_v = (MAX_T - MIN_T) / (MAX_V - MIN_V);
}

float Temperature::getTemperature()
{

  float *values = (float *)malloc(sizeof(float) * ATTEMPTS);
  for (int i = 0; i < ATTEMPTS; i++)
  {
    values[i] = (MIN_T + (voltage - MIN_V) * tick_v) + Settings::getCorrectInt();
  }

  float avarage_value = getAvarageValue(values, ATTEMPTS);
  free(values);
  return static_cast<float>(static_cast<int>(avarage_value * 10)) / 10; // 2.44 => 2.4 ; 2.56 => 2.5
}

Temperature *Temperature::setVolt(float voltage)
{
  this->voltage = voltage;
  return this;
}

int Temperature::getMaxT()
{
  return MAX_T;
}

int Temperature::getMinT()
{
  return MIN_T;
}
