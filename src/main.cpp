#include <U8g2lib.h>
#include <Arduino.h>
#include <OneButton.h>
#include <Wire.h>
#include "ui.h"
#include "debugUi.h"
#include "voltage.h"
#include "temperature.h"
#include "validate.h"
#include "settings.h"
#include "constants.h"

#define IF_SETTINGS_OPEN_RETURN ({  if (!Settings::getSettingsStatus()) return ; })

// button events
void btnPlusOneClick();
void btnPlusLongPress();
void btnMinusOneClick();
void btnMinusLongPress();

/**
От нуля до 15 - обрыв
От 15 до 1000 - изм температура
1000 до 1023 - короткое замыкание
*/

// objects
auto *ui = new UI<OLED_CLASS>();
DebugUI *debug_ui = new DebugUI();
Voltage *volt = new Voltage();
Temperature *temp = new Temperature();
Validate val;
MenuUI *menu = ui->getMenuUI();

// status
bool systemHalted = false;

// buttons
OneButton btn_plus;
OneButton btn_minus;

void ledSetup();
void wireSetup();
void resistorSetup();
void toggleSetup();
void buttonSetup();
void ledProgramStatus(bool status);
void haltSystem();

void setup()
{
  Serial.begin(BOD);
  Serial.println("Configuring..");
#ifdef DEBUG
  debug_ui->printValue("BOD", BOD);
#endif
  // Settings::setUserTemp(48);

  // setups
  ui->begin();
  wireSetup();
  ledSetup();
  resistorSetup();
  toggleSetup();
  buttonSetup();
  ui->initUI();
}

// main loop
void loop()
{
  btn_plus.tick();
  btn_minus.tick();
#ifdef DEBUG
  debug_ui->printTitle("Main loop");
#endif
  float v = volt->conToVolt(analogRead(RESISTOR_PIN));
  float t = temp->setVolt(v)->getTemperature();

  // ui initialization
  ui->setVolt(v);
  ui->setTemperature(t);
#ifdef DEBUG
  debug_ui->fprintValue("Scanner", v);
  debug_ui->fprintValue("Temperature", t);
#endif
  int code = val.setTemperature(t).executePipelineValidate();

  if (code > 0)
  {
    Settings::setErrorStatus(true);
    ui->setError(code);
    systemHalted = true;
    haltSystem();
  }
  else
  {
    Settings::setErrorStatus(false);
    ui->removeError();
    systemHalted = false;
  }

  ledProgramStatus(Settings::getErrorStatus());

  ui->draw();

  if (!systemHalted)
  {
    if (temp->getTemperature() <= Settings::getUserTemp() - Settings::getHysteresis())
    {
      debug_ui->printValue("Burner", "ON");
      Settings::setBurnerStatus(true);
      digitalWrite(BURNER_PIN, HIGH);
    }

    else if (temp->getTemperature() >= Settings::getUserTemp() + Settings::getHysteresis())
    {
      debug_ui->printValue("Burner", "OFF");
      Settings::setBurnerStatus(false);
      digitalWrite(BURNER_PIN, LOW);
    }

    if (digitalRead(TOGGLE_PIN) == HIGH)
      Settings::setSettingsStatus(true);
    else
      Settings::setSettingsStatus(false);
  }
}

void wireSetup()
{
#ifdef DEBUG
  if (CHECK_ADDRESS)
  {
    debug_ui->printTitle("WIRELESS SETUP");
    Serial.println("Scanning for I2C devices...");

    Wire.begin();
    int nDevices = 0;

    byte address, error;
    for (address = 1; address < 127; address++)
    {
      Wire.beginTransmission(address);
      error = Wire.endTransmission();

      if (error == 0)
      {
        debug_ui->bytePrintValue("Founded address", address);
        Serial.print('\n');

        nDevices++;
      }
    }
    if (nDevices == 0)
    {
      Serial.println("No devices found");
    }
  }
#endif
}

void toggleSetup()
{
  pinMode(TOGGLE_PIN, INPUT_PULLUP);
}

void resistorSetup()
{
  debug_ui->printTitle("Resistor");
  pinMode(RESISTOR_PIN, INPUT);
}
void ledSetup()
{
  debug_ui->printTitle("LED SETUP");
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(BURNER_PIN, OUTPUT);
}

void buttonSetup()
{
  const int debounce = 20;
  btn_plus.setup(BUTTON_PIN_PLUS, INPUT_PULLUP, true);
  btn_minus.setup(BUTTON_PIN_MINUS, INPUT_PULLUP, true);
  btn_plus.setDebounceMs(debounce);
  btn_minus.setDebounceMs(debounce);

  btn_plus.attachClick(btnPlusOneClick);
  btn_plus.attachLongPressStart(btnPlusLongPress);
  btn_minus.attachClick(btnMinusOneClick);
  btn_minus.attachLongPressStart(btnMinusLongPress);
}
void ledProgramStatus(bool status)
{
  if (status)
  {
    digitalWrite(RED_LED_PIN, HIGH);
    digitalWrite(GREEN_LED_PIN, LOW);
    digitalWrite(BURNER_PIN, LOW);
  }
  else
  {
    digitalWrite(RED_LED_PIN, LOW);
    digitalWrite(GREEN_LED_PIN, HIGH);
  }
}

void haltSystem()
{
  digitalWrite(BURNER_PIN, LOW);
  Settings::setBurnerStatus(false);
  Settings::setSettingsStatus(false); // show the error overlay instead of the menu
}

void btnPlusLongPress()
{
  IF_SETTINGS_OPEN_RETURN;
#ifdef DEBUG
  Serial.println("longPress btn_plus");
#endif
  ui->getMenuUI()->openValue();
}

void btnPlusOneClick()
{
  IF_SETTINGS_OPEN_RETURN;
  if (menu->isValueOpen())
    menu->increaseValue();
  else
    menu->goToUp();
}

void btnMinusOneClick()
{
  IF_SETTINGS_OPEN_RETURN;

  if (menu->isValueOpen())
    menu->decreaseValue();
  else
    menu->goToDown();
}

void btnMinusLongPress()
{
  IF_SETTINGS_OPEN_RETURN;
#ifdef DEBUG
  Serial.println("longPress btn_minus");
#endif
  ui->getMenuUI()->closeValue();
}
