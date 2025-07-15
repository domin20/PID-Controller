#pragma once
#include "Config.h"

class Integral {
 public:
  explicit Integral(ClockSource timeBase);
  explicit Integral(float timeConstant, ClockSource timeBase);

  float update(float rawInputValue);
  void setTimeConstant(float timeConstant);
  void reset();

 private:
  float _timeConstant;
  float _rawValueDifference;
  float _processedValueDifference;
  float _outputValue;
  float _exponent;

  bool _isRising;
  uint64_t _previousTimeStamp;

  ClockSource _timeBase;
  static constexpr float _INVERSE_EULER = 0.368f; // inverse euler
};
