#pragma once
#include "Config.h"

class Derivative {
 public:
  explicit Derivative(ClockSource clockSource);
  explicit Derivative(float timeConstant, ClockSource clockSource);

  float update(float rawInputValue);
  void setTimeConstant(float timeConstant);

 private:
  float _timeConstant;
  float _rawValueDifference;
  float _processedValueDifference;
  float _previousRawInputValue;
  float _outputValue;
  float _exponent;
  float _difference;
  uint64_t _previousTimeStamp;

  ClockSource _clockSource;
};
