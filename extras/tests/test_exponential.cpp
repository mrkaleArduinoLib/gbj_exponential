/*
  NAME:
  Unit tests of library "gbj_exponential" for smoothing

  DESCRIPTION:
  The test suite provides test cases for calculating filtered value for two
  consecutive values.
  - The test runner is Unity Project - ThrowTheSwitch.org.

  LICENSE:
  This program is free software; you can redistribute it and/or modify
  it under the terms of the MIT License (MIT).

  CREDENTIALS:
  Author: Libor Gabaj
*/
#include "gbj_exponential.h"
#include <Arduino.h>
#include <unity.h>

//******************************************************************************
// Preparation
//******************************************************************************
const float FACTOR_INI = 0.2;
float const FACTOR_NEW = 0.6;
float valInput = 150.0;
float valActual, valExpected, valExpectedOld;

gbj_exponential smooth = gbj_exponential(FACTOR_INI);

//******************************************************************************
// Tests
//******************************************************************************
void test_init(void)
{
  // Algorithm
  valExpected = valExpectedOld = valInput;
  // Testee
  valActual = smooth.getValue(valInput);
  TEST_ASSERT_EQUAL_FLOAT(valExpected, valActual);
}

void test_smoothing(void)
{
  // Algorithm
  valExpected = FACTOR_INI * (valExpected - valExpectedOld) + valExpectedOld;
  valExpectedOld = valExpected;
  // Testee
  valActual = smooth.getValue(valActual);
  TEST_ASSERT_EQUAL_FLOAT(valExpected, valActual);
}

void test_factor_new(void)
{
  valExpected = FACTOR_NEW;
  smooth.setFactor(FACTOR_NEW);
  valActual = smooth.getFactor();
  TEST_ASSERT_EQUAL_FLOAT(valExpected, valActual);
}

void test_factor_min(void)
{
  valExpected = 0.0;
  smooth.setFactor(-2.3);
  valActual = smooth.getFactor();
  TEST_ASSERT_EQUAL_FLOAT(valExpected, valActual);
}

void test_factor_max(void)
{
  valExpected = 1.0;
  smooth.setFactor(2.3);
  valActual = smooth.getFactor();
  TEST_ASSERT_EQUAL_FLOAT(valExpected, valActual);
}

//******************************************************************************
// Run
//******************************************************************************
void setup()
{
  delay(2000);
  UNITY_BEGIN();

  RUN_TEST(test_init);
  RUN_TEST(test_smoothing);
  RUN_TEST(test_factor_new);
  RUN_TEST(test_factor_min);
  RUN_TEST(test_factor_max);

  UNITY_END();
}

void loop() {}