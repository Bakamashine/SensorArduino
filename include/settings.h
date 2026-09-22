#pragma once



class Settings {
private:
  static int userTemperature;
  static bool burnerStatus;
  static bool settingsStatus;
  static bool errorStatus;
  static int burnerDelta;
  static int delta;  // for temperature

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
  static void setBurnerDelta(int);
  static int getBurnerDelta();
  static void setDelta(int);
  static int getDelta();

};