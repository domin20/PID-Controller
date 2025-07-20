#pragma once
#include "Config.h"

class Integral {
 public:
  explicit Integral();
  explicit Integral(ClockSource clockSource);

  float update(float rawInputValue);

  void setClockSource(ClockSource clockSource);
  void setTimeConstant(float timeConstant);
  void setIntegralLimits(float min, float max);
  void reset();

 private:
  float _outputValue;
  uint64_t _previousTimeStamp;

  float _minLimit;
  float _maxLimit;
  bool _isLimitSet = false;

  ClockSource _clockSource;
};
