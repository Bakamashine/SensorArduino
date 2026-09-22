#include <Arduino.h>
#include <stdarg.h>
#include "debugUi.h"
#include "float.h"

#define LINE(size)                     \
  for (int i = 0; i < (size) / 2; i++) \
    Serial.print("#");
void DebugUI::printTitle(const char *v)
{
  const int total_size = 30;
  LINE(total_size);
  size_t v_len = strlen(v);
  size_t t_size = v_len + 3;
  char *t = (char *)malloc(t_size);
  if (!t)
    return;
  t[0] = ' ';
  size_t k = 1;
  for (size_t j = 0; j < v_len; j++)
  {
    t[k++] = v[j];
  }

  if (v_len > 0 && v[v_len - 1] == '\n')
    t[k++] = '\n';
  else
    t[k++] = ' ';
  t[k] = '\0';

  Serial.print(t);
  LINE(total_size);
  Serial.print("\n");
  free(t);
}

void DebugUI::printValue(const char *v1, const char *v2)
{
  auto val = fmtAlloc("%s: %s", v1, v2);
  Serial.println(val);
  free(val);
}
void DebugUI::printValue(const char *v1, long v2)
{
  auto val = fmtAlloc("%s: %d", v1, v2);
  Serial.println(val);
  free(val);
}
void DebugUI::fprintValue(const char *v1, float v2)
{
  char *s = Float::getFloat(v2);
  if (s != NULL)
  {
    printValue(v1, s);
    free(s);
  }
}

void DebugUI::bytePrintValue(const char *v1, byte v2)
{
  size_t t_size = strlen(v1) + 8;
  char *tempString = (char *)malloc(t_size);
  if (tempString != NULL)
  {
    snprintf(tempString, t_size, "%s: 0x%02X", v1, (int)v2);
    Serial.print(tempString);
    free(tempString);
  }
}

char *DebugUI::fmtAlloc(const char *fmt, ...)
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
