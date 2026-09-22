#pragma once
#include <stdint.h>
#include <U8g2lib.h>
#include "menu_ui.h"

#define DEFAULT_SIZE 16

// compile-time check: T must be U8G2 or derived from it
// thanks you, ai
template <typename D, typename B>
struct isU8G2Derived
{
private:
  struct No
  {
  };
  struct Yes
  {
    No no[2];
  };
  static Yes test(B *)
  {
    return Yes();
  }
  static No test(...)
  {
    return No();
  }

public:
  static const bool value = sizeof(test(static_cast<D *>(0))) == sizeof(Yes);
};

template <typename T>
class UI : public T
{
  static_assert(isU8G2Derived<T, U8G2>::value,
                "UI<T>: T must be a U8G2 display class");

private:
  float temperature;
  float voltage;
  int errorCode = 0;
  char tempText[DEFAULT_SIZE];
  char deltaText[DEFAULT_SIZE];
  char voltText[DEFAULT_SIZE];
  char userTempText[DEFAULT_SIZE];
  char burnerText[DEFAULT_SIZE];
  void setFloatText(char *, size_t, const char *, float);

  // void setText(char*, size_t, const char*, ...);
  MenuUI *menuUI;
  void main();

public:
  UI();
  ~UI()
  {
    delete menuUI;
  }
  void initUI();
  void setTemperature(float);
  float getTemperature();
  void setVolt(float);
  void draw();
  void setError(int);
  void removeError();
  void initDelta();
  void userTempInit();
  MenuUI *getMenuUI();
};