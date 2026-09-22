#include "float.h"
#include <Arduino.h>
#include <stdarg.h>

char *Float::fmtAlloc(const char *fmt, ...)
{
  va_list args;
  va_start(args, fmt);
  int needed = vsnprintf(NULL, 0, fmt, args);
  va_end(args);
  if (needed < 0)
    return NULL;
  char *buf = (char *)malloc(needed + 1);
  if (buf != NULL)
  {
    va_start(args, fmt);
    vsnprintf(buf, needed + 1, fmt, args);
    va_end(args);
  }
  return buf;
}

char *Float::getFloat(float v1)
{
  if (v1 < 0)
    v1 = -v1;
  int whole = (int)v1;
  int frac = (int)(v1 * 100) % 100;
  return fmtAlloc("%d.%02d", whole, frac);
}