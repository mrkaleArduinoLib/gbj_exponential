<a id="library"></a>
# gbjFilterExponential
The library smooths a data series by exponential filtering. It calculates a new filtered value from stored previous one and a currently observed value. The theory behind the exponential filter is well described by *Wikipedia* in the article [Exponential smoothing](https://en.wikipedia.org/wiki/Exponential_smoothing). The exponential filter is a weighted combination of the previous estimate (output) with the newest input data, with the sum of the weights equal to 1 so that the output matches the input at steady state.

When the sequence of measurements begins at time **t = 0**, the simplest form of exponential smoothing is given by the formulas:

	S{0} = X{0}; t = 0
	S{t} = a * X{t} + (1 - a) * S{t-1}; t > 0

where

- **X{t}** is the measured (raw) value at some time point
- **S{t}** is the smoothed (filtered) value for the same time point
- **a** is the *smoothing factor* within the range (0, 1) excluding the extreme values, which have no practical sense.
	- The *zero smoothing factor* causes, that all new measured values are ignored and the entire data serie is representing just with the initial value.
	- The *smoothing factor 1* causes, that all previous filtered values are ignored and the entire data serie is representing with the measured values only and no filtering happens.
	- In praxis the smoothing factor is chosen in the range *0.01 to 0.2*.


The above formula can be rewritten into the following predictor-corrector equivalent

	S{t} = S{t-1} + a * (X{t} - S{t-1})

A new smoothed value is predicted as the previous one modified by a correction based on the difference between the new measured value and the previous smoothed value. This form is also the result of deriving the exponential filter formula.

Smoothing factor can be calculated for particular sampling time interval between measurement and the *time constant* of the measured process from the formula

	a = 1 - exp(-Ts/Tk)

where

- **Ts** is the sampling time interval
- **Tk** is the time constant
- **exp()** is the power of Euler number


If the sampling time is very short compared to the time constant, e.g., 5 times, we can calculate the approximate smoothing factor from the formula

	a ~ Ts/Tk


Typical smoothing factors

- **0.632**: The sampling time interval equal to the time constant
- **0.5**: Regular running average
- **0.2**: The sampling time interval ~4.5 times shorter than the time constant
- **0.1**: The sampling time interval ~9.5 times shorter than the time constant
- **0.01**: The sampling time interval ~100 times shorter than the time constant


<a id="dependency"></a>
## Dependency

#### Particle platform
- **Particle.h**: Includes alternative (C++) data type definitions.
- **math.h**: Includes standard C++ mathematics, needed for fabs().

#### Arduino platform
- **Arduino.h**: Main include file for the Arduino SDK version greater or equal to 100.
- **WProgram.h**: Main include file for the Arduino SDK version less than 100.
- **inttypes.h**: Integer type conversions. This header file includes the exact-width integer definitions and extends them with additional facilities provided by the implementation.


<a id="Constants"></a>
## Constants
- **GBJ\_FILTER\_EXPONENTIAL\_VERSION**: Name and semantic version of the library
- **GBJ\_FILTER\_EXPONENTIAL\_FACTOR\_DEF**: Default smoothing factor


<a id="interface"></a>
## Interface
- [gbj_filter_exponential()](#gbj_filter_exponential)
- [init()](#init)
- [getValue()](#getValue)

#### Setters
- [setFactor()](#setFactor)

#### Getters
- [getFactor()](#getFactor)


<a id="gbj_filter_exponential"></a>
## gbj_filter_exponential()
#### Description
Constructor stores the smoothing factor within a class instance object.

#### Syntax
    gbj_filter_exponential(float smoothingFactor);

#### Parameters
<a id="prm_smoothingFactor"></a>
- **smoothingFactor**: Smoothing factor for exponential filtering.
  - *Valid values*: real number 0.0 to 1.0
  - *Default value*: 0.5 for running average ([GBJ\_FILTER\_EXPONENTIAL\_FACTOR\_DEF](#constants))

#### Returns
Object performing the exponential filtering of data.

#### Example
The constructor has the argument defaulted. The constructor instance without the parameter is equivalent to an instance with the argument set by corresponding constant with default value:

``` cpp
gbj_filter_exponential Samples = gbj_filter_exponential(); // It is equivalent to
gbj_filter_exponential Samples = gbj_filter_exponential(GBJ_FILTER_EXPONENTIAL_FACTOR_DEF);
```

#### See also
[setFactor()](#setFactor)

[Back to interface](#interface)


<a id="init"></a>
## init()
#### Description
The method initiates all internal status flags of a class instance object to default values as they are right after power up of a microcontroller. It cause that the next measured is not smoothed, because it is considered as starting value of a data series.

#### Syntax
	void init();

#### Parameters
None

#### Returns
None

[Back to interface](#interface)


<a id="getValue"></a>
## getValue()
#### Description
The method calculates a new filtered value from the input value, previous stored filtered value, and stored smoothing factor in the class instance object.
- Right after microcontroller power up or initiating the instance object by corresponding [method](#init) the very first input value is considered as a previous filtered value, or starting value.

#### Syntax
    float getValue(float value);

#### Parameters
<a id="prm_value"></a>
- **value**: Measured value to be filtered.
  - *Valid values*: float
  - *Default value*: none

#### Returns
Filtered value.

[Back to interface](#interface)


<a id="setFactor"></a>
## setFactor()
#### Description
The method enables changing the smoothing factor dynamically during the measuring (filtering) process.
- Because the smoothing factor depends on the ratio of sampling time interval and time constant of a measured process, at changing some of them it might be useful to update the smoothing factor as well.

#### Syntax
    void setFactor(float smoothingFactor);

#### Parameters
- **smoothingFactor**: The same as the constructor argument [smoothingFactor](#prm_smoothingFactor)

#### Returns
None

#### See also
[getFactor()](#getFactor)

[gbj_filter_exponential()](#gbj_filter_exponential)

[Back to interface](#interface)


<a id="getFactor"></a>
## getFactor()
#### Description
The method returns currently set smoothing factor for the exponential filtering.

#### Syntax
    float getFactor();

#### Parameters
None

#### Returns
Actual smoothing factor.

#### See also
[setFactor()](#setFactor)

[Back to interface](#interface)
