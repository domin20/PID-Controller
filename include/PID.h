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
  float _propotionalGain;
  float _integralGain;
  float _derivativeGain;

  // variables for integral term ..
  float inputValueIt = 0.0f;
  float outputValueIt = 0.0f;

  // variables for derivative term..
  float inputValueDt = 0.0f;
  float outputValueDt = 0.0f;

  Integral _integral;
  Derivative _derivative;
};
