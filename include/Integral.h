#pragma once
#include "Config.h"

class Integral {
 public:
  explicit Integral();
  explicit Integral(ClockSource clockSource);

  float update(float rawInputValue);

  void setClockSource(ClockSource clockSource);
  void setTimeConstant(float timeConstant);
  void reset();

 private:
  float _outputValue;
  uint64_t _previousTimeStamp;

  ClockSource _clockSource;
};
