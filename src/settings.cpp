#include "settings.h"
#include "temperature.h"
#include "page.h"

void Settings::setUserTemp(int t)
{
  userTemperature = t;
}

int Settings::userTemperature = 0;
bool Settings::burnerStatus = false;
bool Settings::settingsStatus = false;
bool Settings::errorStatus = false;
int Settings::delta = 10;

int Settings::getUserTemp()
{
  return userTemperature;
}
void Settings::upUserTemp()
{
  if (Temperature::getMaxT() <= userTemperature)
    return;
  userTemperature++;
}

void Settings::downUserTemp()
{
  if (Temperature::getMinT() >= userTemperature)
    return;
  userTemperature--;
}

bool Settings::getBurnerStatus()
{
  return burnerStatus;
}

void Settings::setBurnerStatus(bool st)
{
  burnerStatus = st;
}

void Settings::setSettingsStatus(bool st)
{
  if (st)
  {
    Page::setCurrentPage(SELECT_SETTINGS);
  }
  else
  {
    Page::setCurrentPage(MAIN_PAGE);
  }
  settingsStatus = st;
}

bool Settings::getSettingsStatus()
{
  return settingsStatus;
}

void Settings::setErrorStatus(bool e)
{
  errorStatus = e;
}

bool Settings::getErrorStatus()
{
  return errorStatus;
}

void Settings::setDelta(int v)
{
  delta = v;
}

int Settings::getDelta()
{
  return delta;
}
