#include <Arduino.h>
#include "ui.h"
#include "voltage.h"
#include "error.h"
#include "settings.h"
#include "page.h"
#include <stdarg.h>
#include "constants.h"
#include "menu_ui.h"
#include "helper_ui.h"


template<typename T>
UI<T>::UI()
  : T(U8G2_R0, /* reset=*/U8X8_PIN_NONE) {
  tempText[0] = '\0';
  deltaText[0] = '\0';
  voltText[0] = '\0';
  userTempText[0] = '\0';
  correcterIntText[0] = '\0';

  menuUI = new MenuUI(this);
}

template<typename T>
MenuUI* UI<T>::getMenuUI() {
  return menuUI;
}


// template<typename T>
// void UI<T>::setText(char* buf, size_t size, const char* fmt, ...) {
//   va_list args;
//   va_start(args, fmt);
//   vsnprintf(buf, size, fmt, args);
//   va_end(args);
// }

template<typename T>
void UI<T>::setFloatText(char* buf, size_t size, const char* label, float v) {
  if (v < 0) v = -v;
  int whole = (int)v;
  int frac = (int)(v * 100) % 100;

  setText(buf, size, "%s: %d.%02d", label, whole, frac);
}

template<typename T>
void UI<T>::setTemperature(float temp) {
  this->temperature = temp;
  this->setFloatText(tempText, sizeof(tempText), "T", temp);
}

template<typename T>
float UI<T>::getTemperature() {
  return temperature;
}

template<typename T>
void UI<T>::setVolt(float volt) {
  voltage = volt;
  this->setFloatText(voltText, sizeof(voltText), "V", volt);
}

template<typename T>
void UI<T>::main() {
  setText(userTempText, sizeof(userTempText), "UT: %d",
                Settings::getUserTemp());
  this->drawStr(TEMP_X, TEMP_Y, tempText);
  this->drawStr(VOLT_X, VOLT_Y, voltText);
  this->drawStr(DELTA_X, DELTA_Y, deltaText);
  this->drawStr(USERTEMP_X, USERTEMP_Y, userTempText);
  snprintf(burnerText, sizeof(burnerText), "Burner: %s", Settings::getBurnerStatus() ? "ON" : "OFF");
  // error overlay, not a replacement screen
  if (Settings::getErrorStatus()) {
    this->drawStr(BURNER_X, BURNER_Y, Error::getErrorMessage(errorCode));
  } else {
    this->drawStr(BURNER_X, BURNER_Y, burnerText);
    this->drawStr(COR_X, COR_Y, correcterIntText);
  }
}

template<typename T>
void UI<T>::draw() {
  this->firstPage();
  do {
    this->setFont(FONT);
    switch (Page::getCurrentPage()) {
      case MAIN:
        main();
        break;
      case SELECT_SETTINGS:
        menuUI->draw();
        break;
      default:
        break;
    }
  } while (this->nextPage());
}

template<typename T>
void UI<T>::setError(int code) {
  errorCode = code;
}

template<typename T>
void UI<T>::removeError() {
  errorCode = 0;
}

template<typename T>
void UI<T>::initDelta() {
  setText(deltaText, sizeof(deltaText), "Delta: %d", Settings::getBurnerDelta());
}

template<typename T>
void UI<T>::userTempInit() {
  setText(userTempText, sizeof(userTempText), "UT: %d", Settings::getUserTemp());
}

template<typename T>
void UI<T>::initUI() {
  setTemperature(0);
  setVolt(0);
  initDelta();
  userTempInit();
  initCorrecterInt();
}

template<typename T>
void UI<T>::initCorrecterInt() {
  setText(correcterIntText, sizeof(correcterIntText), "CorInt: %d", Settings::getDelta());
}

template class UI<OLED_CLASS>;