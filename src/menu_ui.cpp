#include "menu_ui.h"
#include "constants.h"
#include "settings.h"


static const char* const names[MENU_ITEMS_COUNT] = { "Change delta", "Change temperature" };

MenuUI::MenuUI(U8G2* _display)
  : display(_display), selected(CHANGE_DELTA) {
}

void MenuUI::goToUp() {
  selected = (selected - 1 + MENU_ITEMS_COUNT) % MENU_ITEMS_COUNT;
}

void MenuUI::goToDown() {
  selected = (selected + 1) % MENU_ITEMS_COUNT;
}

void MenuUI::draw() {
  display->setFont(FONT);
  int y = 15;
  for (int i = 0; i < MENU_ITEMS_COUNT; i++) {
    display->drawStr(0, y, i == selected ? ">" : " ");
    display->drawStr(8, y, names[i]);
    y += 12;
  }
}

void MenuUI::click() {
  unsigned long now = millis();
  if (now - mil < SETTINGS_CLICK_PERIOD) return;
  mil = now;

  char buf[16];
  switch (selected) {
    case CHANGE_DELTA:
      snprintf(buf, sizeof(buf), "%d", Settings::getDelta());
      display->drawStr(CENTER_X, CENTER_Y, buf);
      break;
  }
}