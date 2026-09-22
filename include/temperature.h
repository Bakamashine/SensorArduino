#pragma once

/**
0 - break
0.5 V = -10 Т (min)
4.5 V = 110 T (max)
5> V - closing


Leaner interpolation:
    https://ru.wikipedia.org/wiki/%D0%9B%D0%B8%D0%BD%D0%B5%D0%B9%D0%BD%D0%B0%D1%8F_%D0%B8%D0%BD%D1%82%D0%B5%D1%80%D0%BF%D0%BE%D0%BB%D1%8F%D1%86%D0%B8%D1%8F
   x = (110-(-10))/(4.5-0.5) = 120/4.0 = 30 T/V

*/

class Temperature
{
private:
  float voltage = 0.0F;
  float tick_v;

public:
  Temperature();
  float getTemperature();
  Temperature *setVolt(float);

  static int getMaxT();
  static int getMinT();
};
