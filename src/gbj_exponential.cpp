#include "gbj_exponential.h"
const String gbj_exponential::VERSION = "GBJ_EXPONENTIAL 1.2.0";

float gbj_exponential::getValue(float value)
{
  if (_init)
  {
    _value = value;
    _init = false;
  }
  else
  {
    _value += getFactor() * (value - _value);
  }
  return _value;
}
