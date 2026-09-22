#pragma once

class DebugUI {
private:
  static char* fmtAlloc(const char*, ...);
public:
  static void printTitle(const char*);
  static void printValue(const char*, const char*);
  static void printValue(const char*, long);
  static void fprintValue(const char*, float);
  static void bytePrintValue(const char*, byte);
};
