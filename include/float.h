#pragma once

class Float
{
public:
  static char *getFloat(float);

private:
  static char *fmtAlloc(const char *fmt, ...);
};
