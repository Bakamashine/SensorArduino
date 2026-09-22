#pragma once

class Settings
{
private:
  static int userTemperature;
  static bool burnerStatus;
  static bool settingsStatus;
  static bool errorStatus;
  static int delta; // burner hysteresis deadband

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
  static void setDelta(int);
  static int getDelta();
};