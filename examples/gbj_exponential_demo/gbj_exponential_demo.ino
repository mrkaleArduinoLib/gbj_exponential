/*
  NAME:
  Demonstration of the exponential filtering

  DESCRIPTION:
  This sketch demonstrates usage of the "gbj_exponential" library.
  - As a measured value the sketch utilizes the random integers within
    the range 0 to 1024 and maps them to the float numbers 0.0 ~ 100.0.
  - For demonstration purposes each data point is output.

  LICENSE:
  This program is free software; you can redistribute it and/or modify
  it under the terms of the MIT License (MIT).

  CREDENTIALS:
  Author: Libor Gabaj
*/
#define SKETCH "GBJ_FILTER_EXPONENTIAL_DEMO 1.1.0"

#if defined(__AVR__)
  #include <Arduino.h>
  #include <inttypes.h>
#elif defined(ESP8266) || defined(ESP32)
  #include <Arduino.h>
#elif defined(PARTICLE)
  #include <Particle.h>
#endif
#include "gbj_exponential.h"

const unsigned int PERIOD_MEASURE = 3000;
const unsigned int SENSOR_DATA_MAX = 1023;
const float COEF_DEMO = 100.0 / float(SENSOR_DATA_MAX);
const float COEF_FILTER_FACTOR = 0.2; // Smoothing factor
float demoData, filterData;

gbj_exponential filter = gbj_exponential(COEF_FILTER_FACTOR);

void setup()
{
  Serial.begin(115200);
  delay(2000);
  Serial.print("Sketch: ");
  Serial.println(SKETCH);
  Serial.print("Library: ");
  Serial.println(gbj_exponential::VERSION);
  Serial.println("---");
  Serial.print("Smoothing factor: ");
  Serial.println(filter.getFactor(), 1);
  Serial.println("Measured\tFiltered");
}

void loop()
{
  demoData = COEF_DEMO * (float)random(SENSOR_DATA_MAX + 1); // Measured data
  filterData = filter.getValue(demoData); // Filtered data
  Serial.print(demoData, 1);
  Serial.print("\t");
  Serial.println(filterData, 1);
  delay(PERIOD_MEASURE);
}
