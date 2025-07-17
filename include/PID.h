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

  void setIntegralTimeConstant(float timeConstant);
  void setDerivativeTimeConstant(float timeConstant);

  float update(float error);

 private:
  float _proportionalGain;
  float _integralGain;
  float _derivativeGain;

  // variables for integral term ..
  float _inputValueIt = 0.0f;
  float _outputValueIt = 0.0f;

  // variables for derivative term..
  float _inputValueDt = 0.0f;
  float _outputValueDt = 0.0f;

  Integral _integral;
  Derivative _derivative;
};
