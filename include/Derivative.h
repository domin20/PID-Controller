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
  float _previousInput;
  float _outputValue;
  uint64_t _previousTimeStamp;

  ClockSource _clockSource;
};
