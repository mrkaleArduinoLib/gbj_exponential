/*
  NAME:
  Unit tests of library "gbj_filter_exponential" for smoothing.

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
#include <Arduino.h>
#include <unity.h>
#include <gbj_filter_exponential.h>

float factor_ini = 0.2;
float factor_new = 0.6;
float value_ini = 150.0;
float value_cur = 200.0;
float value_new;

gbj_filter_exponential Filter = gbj_filter_exponential(0.2);

void setup_test()
{
    // Set initial value for filtering
    Filter.getValue(value_ini);
}

void test_smoothing(void)
{
    // 0.2 * (200.0 - 150.0) + 150.0 = 160.0
    value_new = factor_ini * (value_cur - value_ini) + value_ini;
    TEST_ASSERT_EQUAL_FLOAT(value_new, Filter.getValue(value_cur));
}

void test_change_factor(void)
{
    Filter.setFactor(factor_new);
    value_ini = value_new;
    // 0.6 * (200.0 - 160.0) + 160.0 = 184.0
    value_new = factor_new * (value_cur - value_ini) + value_ini;
    TEST_ASSERT_EQUAL_FLOAT(value_new, Filter.getValue(value_cur));
}


void setup() {
    setup_test();
    UNITY_BEGIN();

    RUN_TEST(test_smoothing);
    RUN_TEST(test_change_factor);

    UNITY_END();
}

void loop(){}