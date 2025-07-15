#pragma once
#include "Config.h"

class Derivative {
 public:
  explicit Derivative(ClockSource timeBase);
  explicit Derivative(float timeConstant, ClockSource timeBase);

  float update(float rawInputValue);
  void setTimeConstant(float timeConstant);

 private:
  static const float _INVERSE_EULER; // inverse euler

  float _timeConstant;
  float _rawValueDifference;
  float _processedValueDifference;
  float _previousRawInputValue;
  float _outputValue;
  float _exponent;
  float _difference;
  uint64_t _previousTimeStamp;

  ClockSource _timeBase;
};
