#include "menu_ui.h"
#include "constants.h"
#include "settings.h"
#include "page.h"

static const char *const names[MENU_ITEMS_COUNT] = {"Change delta", "Change temperature"};

MenuUI::MenuUI(U8G2 *_display)
    : display(_display), selected(CHANGE_DELTA)
{
}

void MenuUI::goToUp()
{
  selected = (selected - 1 + MENU_ITEMS_COUNT) % MENU_ITEMS_COUNT;
}

void MenuUI::goToDown()
{
  selected = (selected + 1) % MENU_ITEMS_COUNT;
}

void MenuUI::draw()
{
  display->setFont(FONT);

  if (valueOpen)
  {
    char buf[64];
    int value = (selected == CHANGE_DELTA) ? Settings::getDelta() : Settings::getUserTemp();
    snprintf(buf, sizeof(buf), (selected == CHANGE_DELTA) ? "Delta: %d" : "UserTemperature: %d", value);
    display->drawStr(TEMP_X, TEMP_Y, buf);
    return;
  }

  int y = 15;
  for (int i = 0; i < MENU_ITEMS_COUNT; i++)
  {
    display->drawStr(0, y, i == selected ? ">" : " ");
    display->drawStr(8, y, names[i]);
    y += 12;
  }
}

void MenuUI::openValue()
{
  valueOpen = true;
}

void MenuUI::closeValue()
{
  valueOpen = false;
}

bool MenuUI::isValueOpen()
{
  return valueOpen;
}

void MenuUI::increaseValue()
{
  if (selected == CHANGE_DELTA)
  {
    int d = Settings::getDelta() + 1;
    if (d <= MAX_DELTA)
      Settings::setDelta(d);
  }
  else
  {
    Settings::upUserTemp();
  }
}

void MenuUI::decreaseValue()
{
  if (selected == CHANGE_DELTA)
  {
    // int d = Settings::getDelta() - 1;
    // if (d >= MIN_DELTA)
    int d = Settings::getDelta();
    if (!(d < MIN_DELTA) && d<=MAX_DELTA)
      Settings::setDelta(d);
  }
  else
  {
    Settings::downUserTemp();
  }
}