#pragma once

#include "Derivative.h"
#include "Integral.h"

class PID {
 public:
  explicit PID(TimeSource timeBase);
  explicit PID(float propotionalGain, TimeSource timeBase);
  PID(float propotionalGain, float integralGain, TimeSource timeBase);
  PID(float propotionalGain, float integralGain, float derivativeGain, TimeSource timeBase);
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

  TimeSource _timeBase;
  Integral _integral = Integral(_timeBase);
  Derivative _derivative = Derivative(_timeBase);
};
