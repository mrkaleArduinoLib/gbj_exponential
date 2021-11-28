#include "gbj_exponential.h"
const String gbj_exponential::VERSION = "GBJ_EXPONENTIAL 1.2.1";

float gbj_exponential::getValue(float value)
{
  if (init_)
  {
    value_ = value;
    init_ = false;
  }
  else
  {
    value_ += getFactor() * (value - value_);
  }
  return value_;
}
