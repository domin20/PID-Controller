#pragma once

#include "Derivative.h"
#include "Integral.h"

class PID {
 public:
  explicit PID(ClockSource clockSource);
  explicit PID(float propotionalGain, ClockSource clockSource);
  PID(float propotionalGain, float integralGain, ClockSource clockSource);
  PID(float propotionalGain, float integralGain, float derivativeGain, ClockSource clockSource);
  ~PID() {};

  void setIntegralTimeConstant(float timeConstant);
  void setDerivativeTimeConstant(float timeConstant);

  float update(float error);

 private:
  float integralUpdate(float inuptValue);
  float derivativeUpdate(float inputValue);

 private:
  float _propotionalGain;
  float _integralGain;
  float _derivativeGain;

  Integral _integral;
  Derivative _derivative;
};
