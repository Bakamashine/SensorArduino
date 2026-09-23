#pragma once
#include <Arduino.h>
template <typename T>
T getAvarageValue(T *array, size_t size)
{
  if (size == 0)
    return 0;
  T sum = 0;
  for (size_t i = 0; i < size; i++)
    sum += array[i];
  return sum / (T)size;
}