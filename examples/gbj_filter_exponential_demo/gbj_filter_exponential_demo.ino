/*
  NAME:
  Demonstration of the exponential filtering.

  DESCRIPTION:
  This sketch demonstrates the exponential filtering by gbjFilterExponential library.
  - As a measured value the sketch utilizes the random integers within
    the range 0 to 1023.
  - For demonstration purposes each data point is output.

  LICENSE:
  This program is free software; you can redistribute it and/or modify
  it under the terms of the MIT License (MIT).

  CREDENTIALS:
  Author: Libor Gabaj
*/
#include "gbj_filter_exponential.h"
#define SKETCH "GBJ_FILTER_EXPONENTIAL_DEMO 1.0.1"

const unsigned int PERIOD_MEASURE = 3000; // Time in miliseconds between measurements

// Upper limit of random values for mimicking real physical measurement
const unsigned int SENSOR_DATA_MAX = 1023;

// Coefficient for mimicking real physical value within the range 0.0 to 100.0
const float COEF_DEMO = 100.0 / 1023.0;

// Variables and constants for measurement
const float COEF_FILTER_FACTOR = 0.2; // The smoothing factor for exponential filtering
float demoData, filterData;
gbj_filter_exponential Filter = gbj_filter_exponential(COEF_FILTER_FACTOR);

void setup()
{
  Serial.begin(9600);
  Serial.println(SKETCH);
  Serial.println("Libraries:");
  Serial.println(gbj_filter_exponential::VERSION);
  Serial.println("---");
  Serial.print("Smoothing factor: ");
  Serial.println(Filter.getFactor(), 4);
  Serial.println("Measured\tFiltered");
}

void loop()
{
  demoData = COEF_DEMO * (float)random(SENSOR_DATA_MAX + 1); // Measured data
  filterData = Filter.getValue(demoData);                    // Filtered data
  Serial.print(demoData, 1);
  Serial.print("\t\t");
  Serial.println(filterData, 1);
  delay(PERIOD_MEASURE);
}
