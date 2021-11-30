#include "gbj_exponential.h"
const String gbj_exponential::VERSION = "GBJ_EXPONENTIAL 1.3.0";

float gbj_exponential::getValue(float value)
{
  if (init_)
  {
    value_ = value;
    init_ = false;
  }
  else
  {
    value_ += factor_ * (value - value_);
  }
  return value_;
}
