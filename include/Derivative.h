#pragma once
#include "Config.h"

class Derivative {
 public:
  explicit Derivative();
  explicit Derivative(TimeSource timeBase);
  explicit Derivative(float timeConstant, TimeSource timeBase);

  void setTimeBase(TimeSource timeBase);

  float update(float rawInputValue);
  void setTimeConstant(float timeConstant);

 private:
  float _timeConstant;
  static const float _INVERSE_EULER; // inverse euler
  float _rawValueDifference;
  float _processedValueDifference;
  float _previousRawInputValue;
  float _outputValue;
  float _exponent;
  float _difference;

  uint64_t _previousTimeStamp;

  TimeSource _timeBase;
};