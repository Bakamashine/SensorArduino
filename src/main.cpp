#include <U8g2lib.h>
#include "Arduino.h"
#include <Wire.h>
#include "ui.h"
#include "debugUi.h"
#include "voltage.h"
#include "temperature.h"
#include "validate.h"
#include "settings.h"
#include "constants.h"


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

// status
bool systemHalted = false;

// buttons
// int lastButtonState = HIGH;
// int buttonState;
// unsigned long lastDebounceTime()

void ledSetup();
void wireSetup();
void resistorSetup();
void toggleSetup();
void buttonSetup();
void ledProgramStatus(bool status);
void haltSystem();

void setup() {
  Serial.begin(BOD);
  Serial.println("Configuring..");
  debug_ui->printValue("BOD", BOD);
  Settings::setUserTemp(48);

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
void loop() {
  debug_ui->printTitle("Main loop");
  float v = volt->conToVolt(analogRead(RESISTOR_PIN));
  float t = temp->setVoltage(v)->getTemperature();

  // ui initialization
  ui->setVolt(v);
  ui->setTemperature(t);
  debug_ui->fprintValue("Scanner", v);
  debug_ui->fprintValue("Temperature", t);

  int code = val.setTemperature(t).executePipelineValidate();

  if (code > 0) {
    Settings::setErrorStatus(true);
    ui->setError(code);
    systemHalted = true;
    haltSystem();
  } else {
    Settings::setErrorStatus(false);
    ui->removeError();
    systemHalted = false;
  }

  ledProgramStatus(Settings::getErrorStatus());

  ui->draw();

  if (!systemHalted) {
    if (temp->getTemperature() <= Settings::getUserTemp() - Settings::getBurnerDelta()) {
      debug_ui->printValue("Burner", "ON");
      Settings::setBurnerStatus(true);
      digitalWrite(BURNER_PIN, HIGH);
      delay(BUTTON_PERIOD);
    }

    else if (temp->getTemperature() >= Settings::getUserTemp() + Settings::getBurnerDelta()) {
      debug_ui->printValue("Burner", "OFF");
      Settings::setBurnerStatus(false);
      digitalWrite(BURNER_PIN, LOW);
      delay(BUTTON_PERIOD);
    }


    if (digitalRead(TOGGLE_PIN) == HIGH) Settings::setSettingsStatus(true);
    else Settings::setSettingsStatus(false);

    // settings
    if (Settings::getSettingsStatus()) {
      if (digitalRead(BUTTON_PIN_PLUS) == LOW) {
        ui->getMenuUI()->goToUp();
      }
      if (digitalRead(BUTTON_PIN_MINUS) == LOW) {
        ui->getMenuUI()->goToDown();
      }
    }
  }
}

void wireSetup() {
  if (CHECK_ADDRESS) {
    debug_ui->printTitle("WIRELESS SETUP");
    Serial.println("Scanning for I2C devices...");

    Wire.begin();
    int nDevices = 0;


    byte address, error;
    for (address = 1; address < 127; address++) {
      Wire.beginTransmission(address);
      error = Wire.endTransmission();

      if (error == 0) {
        debug_ui->bytePrintValue("Founded address", address);
        Serial.print('\n');

        nDevices++;
      }
    }
    if (nDevices == 0) {
      Serial.println("No devices found");
    }
  }
}

void toggleSetup() {
  pinMode(TOGGLE_PIN, INPUT_PULLUP);
}

void resistorSetup() {
  debug_ui->printTitle("Resistor");
  pinMode(RESISTOR_PIN, INPUT);
}
void ledSetup() {
  debug_ui->printTitle("LED SETUP");
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(BURNER_PIN, OUTPUT);
}

void buttonSetup() {
  pinMode(BUTTON_PIN_PLUS, INPUT_PULLUP);
  pinMode(BUTTON_PIN_MINUS, INPUT_PULLUP);
}
void ledProgramStatus(bool status) {
  if (status) {
    digitalWrite(RED_LED_PIN, HIGH);
    digitalWrite(GREEN_LED_PIN, LOW);
    digitalWrite(BURNER_PIN, LOW);
  } else {
    digitalWrite(RED_LED_PIN, LOW);
    digitalWrite(GREEN_LED_PIN, HIGH);
  }
}

void haltSystem() {
  digitalWrite(BURNER_PIN, LOW);
  Settings::setBurnerStatus(false);
  Settings::setSettingsStatus(false);  // show the error overlay instead of the menu
}
