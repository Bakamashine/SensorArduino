#include "helper_ui.h"
#include <stdarg.h>

void setText(char* buf, size_t size, const char* fmt, ...) {
  va_list args;
  va_start(args, fmt);
  vsnprintf(buf, size, fmt, args);
  va_end(args);
}