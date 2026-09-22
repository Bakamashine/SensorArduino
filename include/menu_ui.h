#pragma once

#include <U8g2lib.h>

enum MenuItem
{
  CHANGE_DELTA,
  CHANGE_TEMPERATURE,
  MENU_ITEMS_COUNT,
};

class MenuUI
{
private:
  U8G2 *display;
  int selected;
  bool valueOpen = false;

public:
  MenuUI(U8G2 *display);
  void goToUp();
  void goToDown();
  void draw();
  void openValue();
  void closeValue();
  bool isValueOpen();
  void increaseValue();
  void decreaseValue();
};