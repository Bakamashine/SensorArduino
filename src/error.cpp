#include "error.h"

Error::Error() {}

void Error::setErrorCode(int code)
{
  this->code = code;
}

void Error::setErrorCodeAndStatus(int code)
{
  if (code > 0)
    setStatusError();
  this->code = code;
}
int Error::getErrorCode()
{
  return code;
}

bool Error::getStatusError()
{
  return status;
}

void Error::setStatusError()
{
  status = true;
}

const char *Error::getErrorMessage(int code)
{
  switch (code)
  {
  case 1:
    return "Error 1: Closing";
  case 2:
    return "Error 2: Break";
  case 3:
    return "Error 3: Burner is broken";
  default:
    return "No error";
  }
}