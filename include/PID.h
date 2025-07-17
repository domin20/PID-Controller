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

  void setDerivativeTimeConstant(float timeConstant);

  float getProportionalTerm() { return _proportionalTermValue; }
  float getIntegralTerm() { return _integralTermValue; }
  float getDerivativeTerm() { return _derivativeTermValue; }

  float update(float error);

 private:
  float _proportionalGain;
  float _integralGain;
  float _derivativeGain;

  float _proportionalTermValue = 0.0f;
  float _integralTermValue = 0.0f;
  float _derivativeTermValue = 0.0f;

  Integral _integral;
  Derivative _derivative;
};