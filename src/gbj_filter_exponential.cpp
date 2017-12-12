#include "gbj_filter_exponential.h"


// Constructor
gbj_filter_exponential::gbj_filter_exponential(float smoothingFactor)
{
  setFactor(smoothingFactor);
  init();
}


// Initialize all status variables
void gbj_filter_exponential::init()
{
  _init = true;
}


// Filtering
float gbj_filter_exponential::getValue(float value)
{
  if (_init)
  {
    _value = value;
    _init = false;
  }
  else
  {
    _value += _factor * (value - _value);
  }
  return _value;
}


//------------------------------------------------------------------------------
// Setters
//------------------------------------------------------------------------------
void gbj_filter_exponential::setFactor(float smoothingFactor)
{
  _factor = constrain(fabs(smoothingFactor), 0.0, 1.0);
}


//------------------------------------------------------------------------------
// Getters
//------------------------------------------------------------------------------
float gbj_filter_exponential::getFactor() { return _factor; };
