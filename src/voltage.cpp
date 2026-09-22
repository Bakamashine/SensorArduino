#include "voltage.h"

#define MAX_ACP 1023
#define ARDUINO_VOLTAGE 5

float Voltage::conToVolt(int analog)
{
  return (float)analog * ARDUINO_VOLTAGE / MAX_ACP;
}
