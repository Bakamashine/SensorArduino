#include <Arduino.h>
#include "temperature.h"
#include "settings.h"

#define BREAK 0
#define MIN_V 0.5F
#define MIN_T -10
#define MAX_V 4.5F
#define MAX_T 110

Temperature::Temperature() {
  tick_v = (MAX_T - MIN_T) / (MAX_V - MIN_V);
}

float Temperature::getTemperature() {
  if (voltage <= MIN_V) return MIN_T;
  if (voltage >= MAX_V) return MAX_T;
  // if Settings::getDelta is negative, then substraction will be performed. -+ = -
  return (MIN_T + (voltage - MIN_V) * tick_v) + Settings::getDelta();
}


Temperature* Temperature::setVoltage(float voltage) {
  this->voltage = voltage;
  return this;
}

int Temperature::getMaxT() {
  return MAX_T;
}

int Temperature::getMinT() {
  return MIN_T;
}
