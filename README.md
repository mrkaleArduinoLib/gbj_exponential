<a id="library"></a>

# gbj_exponential
The library statistically smooths a data serie by exponential filtering. It calculates a new smoothed value from one smoothed previously and provided currently, e.g., a sample from a sensor reading. The theory behind the exponential filter is well described by *Wikipedia* in the article [Exponential smoothing](https://en.wikipedia.org/wiki/Exponential_smoothing).

* The exponential filter is a weighted combination of the previous estimate (output) with the newest input data, with the sum of the weights equal to 1, so that the output matches the input at steady state.
* The library does not define a valid range of values to be smoothed. That range and checking values against it should be provided externally.

## Fundamental functionality
When the sequence of measurements begins at time `t = 0`, the simplest form of exponential smoothing is given by the formulas:

	S{0} = X{0}; t = 0
	S{t} = a * X{t} + (1 - a) * S{t-1}; t > 0

where

* **X{t}** is the measured (raw) value at some time point
* **S{t}** is the smoothed (filtered) value for the same time point
* **a** is the *smoothing factor* within the range (0, 1) excluding the extreme values, which have no practical sense.
	* The *zero smoothing factor* causes, that all new measured values are ignored and the entire data series is representing just with the initial value.
	* The *smoothing factor 1* causes, that all previous filtered values are ignored and the entire data series is representing with the measured values only and no filtering happens.
	* In praxis the smoothing factor is chosen within the range `0.01 ~ 0.2`.

The above formula can be rewritten into the following predictor-corrector equivalent

	S{t} = S{t-1} + a * (X{t} - S{t-1})

A new smoothed value is predicted as the previous one modified by a correction based on the difference between the new measured value and the previous smoothed value. This form is also the result of deriving the exponential filter formula.

Smoothing factor can be calculated for particular sampling time interval between measurement and the _time constant_ of the measured process from the formula

	a = 1 - exp(-Ts/Tk)

where

* **Ts** is the sampling time interval
* **Tk** is the time constant
* **exp()** is the power of Euler number

If the sampling time is very short compared to the time constant, e.g., 5 times, we can calculate the approximate smoothing factor from the formula

	a ~ Ts/Tk


## Typical smoothing factors
* **0.632**: The sampling time interval equal to the time constant.
* **0.5**: Regular running average.
* **0.2**: The sampling time interval ~4.5 times shorter than the time constant.
* **0.1**: The sampling time interval ~9.5 times shorter than the time constant.
* **0.01**: The sampling time interval ~100 times shorter than the time constant.


<a id="dependency"></a>

## Dependency

#### Arduino platform
* **Arduino.h**: Main include file for the Arduino SDK version greater or equal to 100.
* **inttypes.h**: Integer type conversions. This header file includes the exact-width integer definitions and extends them with additional facilities provided by the implementation.

#### Espressif platform
* **Arduino.h**: Main include file for the Arduino platform.


<a id="tests"></a>

## Unit testing
The subfolder `tests` in the folder `extras`, i.e., `gbj_exponential/extras/test`, contains testing files, usually just one, with unit tests of library [gbj_exponential](#library) executable by [Unity](http://www.throwtheswitch.org/unity) test runner. Each testing file should be placed in an individual test folder of a particular project, usually in the structure `test/<testname>/<testfile>`.
* **test_exponential.cpp**: Test file providing test cases for statistical smoothing calculation and all relevant public methods.


<a id="interface"></a>

## Interface
* [gbj_exponential()](#gbj_exponential)
* [init()](#init)
* [getValue()](#getValue)
* [setFactor()](#setFactor)
* [getFactor()](#getFactor)


<a id="gbj_exponential"></a>

## gbj_exponential()

#### Description
Constructor stores the smoothing factor within a class instance object and initiate it.
* The library instance object does not execute any checks agains valid range of values. The improper values should be avoided for inputing to this method externally.

#### Syntax
    gbj_exponential(float smoothingFactor)

#### Parameters
* **smoothingFactor**: Smoothing factor for exponential filtering.
  * *Valid values*: real number 0.0 ~ 1.0
  * *Default value*: 0.5 (running average)

#### Returns
Object performing the exponential filtering of data.

#### See also
[setFactor()](#setFactor)

[Back to interface](#interface)


<a id="init"></a>

## init()

#### Description
The method initiates all internal resources of a class instance object to default values as they are right after creating a library instance object.
* It cause that the next measured value is not smoothed, because it is considered as starting value of a data serie.

#### Syntax
	void init()

#### Parameters
None

#### Returns
None

[Back to interface](#interface)


<a id="getValue"></a>

## getValue()

#### Description
The overloaded method either calculates a new smoothed value or returns recently smoothed one.
* The calculation is executed from the input value, previous stored smoothed value, and stored smoothing factor in the class instance object.
* Right after initiation either by creating the [instance object](#gbj_exponential) or calling the  method [init()](#init) the very first input value is considered as a previous smoothed value, or starting value.
* The method without any input parameter returns recently smoothed value. It is useful if there is no variable used for the smoothed value in an application and the recent value is needed.
* The method can be used as a "last good value" at external filtering against a valid range of values.

#### Syntax
    float getValue(float value)
    float getValue()

#### Parameters
* **value**: Value (sample) to be filtered.
  * *Valid values*: float
  * *Default value*: none

#### Returns
Currently or recently smoothed value.

[Back to interface](#interface)


<a id="setFactor"></a>

## setFactor()

#### Description
The method enables changing the smoothing factor dynamically during the smoothing process.
* Because the smoothing factor depends on the ratio of sampling time interval and time constant of a measured process, at changing some of them it might be useful to update the smoothing factor as well.

#### Syntax
    void setFactor(float smoothingFactor)

#### Parameters
* **smoothingFactor**: The same as the [constructor's](#gbj_exponential) argument.

#### Returns
None

#### See also
[getFactor()](#getFactor)

[gbj_exponential()](#gbj_exponential)

[Back to interface](#interface)


<a id="getFactor"></a>

## getFactor()

#### Description
The method returns currently stored smoothing factor for the exponential filtering.

#### Syntax
    float getFactor()

#### Parameters
None

#### Returns
Actual smoothing factor.

#### See also
[setFactor()](#setFactor)

[Back to interface](#interface)
