/*
  NAME:
  gbj_exponential

  DESCRIPTION:
  The library smooths (filters) a data series by exponential filtering.
  - A new filtered value is calculated from stored previous one and
    a currently measured value.
  - The series of filtered values represents a series of really measured
    (usually measured and/or calculated) values with reduced digital noise.

  LICENSE:
  This program is free software; you can redistribute it and/or modify
  it under the terms of the license GNU GPL v3
  http://www.gnu.org/licenses/gpl-3.0.html (related to original code) and MIT
  License (MIT) for added code.

  CREDENTIALS:
  Author: Libor Gabaj
  GitHub: https://github.com/mrkaleArduinoLib/gbj_exponential.git

  CREDITS:
  Wikipedia: Exponential smoothing
  (https://en.wikipedia.org/wiki/Exponential_smoothing)
*/
#ifndef GBJ_EXPONENTIAL_H
#define GBJ_EXPONENTIAL_H

#if defined(__AVR__)
  #include "Arduino.h"
  #include <inttypes.h>
#elif defined(ESP8266)
  #include <Arduino.h>
#elif defined(ESP32)
  #include <Arduino.h>
#elif defined(PARTICLE)
  #include "Particle.h"
  #include "math.h"
#endif

class gbj_exponential
{
public:
  static const String VERSION;

  /*
    Constructor

    DESCRIPTION:
    Constructor stores the smoothing factor within a class instance object
    with initial internal status flags.

    PARAMETERS:
    smoothingFactor - Smoothing factor for exponential filtering.
      - Data type: float
      - Default value: 0.5
      - Limited range: 0.0 ~ 1.0

    RETURN:  object
  */
  inline gbj_exponential(float smoothingFactor = 0.5)
  {
    setFactor(smoothingFactor);
    init();
  }

  /*
    Reset all status flags

    DESCRIPTION:
    The method initiates all internal status flags of a class
    instance object to default values as they are right after power up of
    a microcontroler.

    PARAMETERS: none

    RETURN: none
  */
  inline void init(void) { flInit_ = true; };

  /*
    Calculate new filtered value from measured value or return recent one

    DESCRIPTION:
    The overloaded method calculates a new filtered value from the input value,
    previous stored filtered value, and stored smoothing factor in the class
    instance object.
    - Right after microcontroler power up or initiating the instance object
      by corresponding method the very first input value is considered as
      a previous filtered value, or starting value.
    - The method without any input parameter returns recently filtered value.

    PARAMETERS:
    value - Measured value to be filtered.
      - Data type: float, void
      - Default value: none
      - Limited range: rational numbers

    RETURN: Filtered value
  */
  inline float getValue(void) { return value_; }
  inline float getValue(float value)
  {
    if (flInit_)
    {
      value_ = value;
      flInit_ = false;
    }
    else
    {
      value_ += factor_ * (value - value_);
    }
    return value_;
  }

  inline void setFactor(float factor)
  {
    factor_ = constrain(fabs(factor), 0.0, 1.0);
  }
  inline float getFactor() { return factor_; }

private:
  bool flInit_; // Flag about initial filtering
  float factor_; // Smoothing factor
  float value_; // Recent filtered value
};

#endif
