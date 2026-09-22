#pragma once

class Settings
{
private:
  static int userTemperature;
  static bool burnerStatus;
  static bool settingsStatus;
  static bool errorStatus;
  static int hysteresis; // burner hysteresis deadband
  static int correctInt;

public:
  static void setUserTemp(int);
  static int getUserTemp();
  static void setSettingsStatus(bool);
  static bool getSettingsStatus();
  static void setErrorStatus(bool);
  static bool getErrorStatus();
  static void upUserTemp();
  static void downUserTemp();
  static bool getBurnerStatus();
  static void setBurnerStatus(bool);
  static void setHysteresis(int);
  static int getHysteresis();
  static void setCorrectInt(int);
  static int getCorrectInt();
};