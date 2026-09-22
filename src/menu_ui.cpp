#include "menu_ui.h"
#include "constants.h"
#include "settings.h"
#include "page.h"

static const char *const names[MENU_ITEMS_COUNT] = {"Change hysteresis", "Change temperature", "Ch. value for cor. sensor"};

MenuUI::MenuUI(U8G2 *_display)
    : display(_display), selected(CHANGE_HYSTERESIS)
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
    char buf[32];
    const char *label;
    int value;
    switch (selected)
    {
    case CHANGE_HYSTERESIS:
      label = "Hysteresis:";
      value = Settings::getHysteresis();
      break;
    case CHANGE_CORRECT_INT:
      label = "CorrectInt:";
      value = Settings::getCorrectInt();
      break;
    default:
      label = "UserTemp:";
      value = Settings::getUserTemp();
      break;
    }
    snprintf(buf, sizeof(buf), "%s %d", label, value);
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
  switch (selected)
  {
  case CHANGE_HYSTERESIS:
  {
    int d = Settings::getHysteresis() + 1;
    if (d >= MIN_DELTA && d <= MAX_DELTA)
      Settings::setHysteresis(d);
    break;
  }
  case CHANGE_TEMPERATURE:
    Settings::upUserTemp();
    break;
  case CHANGE_CORRECT_INT:
    Settings::setCorrectInt(Settings::getCorrectInt() + 1);
    break;
  default:
    break;
  }
}

void MenuUI::decreaseValue()
{
  switch (selected)
  {
  case CHANGE_HYSTERESIS:
  {
    int d = Settings::getHysteresis() - 1;
    if (d >= MIN_DELTA && d <= MAX_DELTA)
      Settings::setHysteresis(d);
    break;
  }
  case CHANGE_TEMPERATURE:
    Settings::downUserTemp();
    break;
  case CHANGE_CORRECT_INT:
    Settings::setCorrectInt(Settings::getCorrectInt() - 1);
    break;
  default:
    break;
  }
}