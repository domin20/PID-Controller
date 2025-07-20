#pragma once

#include "Derivative.h"
#include "Integral.h"

class PID {
 public:
  explicit PID(ClockSource clockSource);
  explicit PID(float proportionalGain, ClockSource clockSource);
  PID(float proportionalGain, float integralGain, ClockSource clockSource);
  PID(float proportionalGain, float integralGain, float derivativeGain, ClockSource clockSource);
  ~PID() {};

  void setIntegralLimits(float min, float max);
  void setDerivativeTimeConstant(float timeConstant);

  float getIntegralTermValue() { return _integral.getOutputValue(); }
  float getDerivativeTermValue() { return _derivative.getOutputValue(); }

  float update(float error);

 private:
  float _proportionalGain;
  float _integralGain;
  float _derivativeGain;

  float _proportionalTermResultValue = 0.0f;
  float _integralTermResultValue = 0.0f;
  float _derivativeTermResultValue = 0.0f;

  Integral _integral;
  Derivative _derivative;
};