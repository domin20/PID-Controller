#pragma once

#include <stdint.h>

using ClockSource = uint64_t (*)();

class PID {
 public:
  explicit PID(ClockSource clockSource);
  explicit PID(float proportionalGain, ClockSource clockSource);
  PID(float proportionalGain, float integralGain, ClockSource clockSource);
  PID(float proportionalGain, float integralGain, float derivativeGain, ClockSource clockSource);
  ~PID() {};

  void setIntegralLimits(float min, float max);
  void setDerivativeTimeConstant(float timeConstant);

  float getIntegralTermValue() { return _integralOutputValue; }
  float getDerivativeTermValue() { return _derivativeOutputValue; }

  float update(float error);

 private:
  ClockSource _clockSource = nullptr;
  float _proportionalGain;
  float _integralGain;
  float _derivativeGain;

  float _proportionalTermResultValue = 0.0f;
  float _integralTermResultValue = 0.0f;
  float _derivativeTermResultValue = 0.0f;

  float _integralOutputValue = 0;
  uint64_t _integralPreviousTimeStamp = 0;

  float _minIntegralLimit;
  float _maxIntegralLimit;
  bool _isIntegralLimitSet = false;

  uint64_t _derivativePreviousTimeStamp = 0;
  float _derivativePreviousError = 0;
  float _derivativeOutputValue = 0;
  float _derivativeTimeConstant = 1.0f;
};