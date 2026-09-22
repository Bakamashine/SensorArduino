#pragma once

class Error
{
private:
  bool status = false;
  int code = 0;

public:
  Error();
  void setErrorCode(int code);
  int getErrorCode();
  bool getStatusError();
  void setStatusError();
  static const char *getErrorMessage(int code);
  void setErrorCodeAndStatus(int code);
};