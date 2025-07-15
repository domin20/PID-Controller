#include "PID.h"

PID::PID(TimeSource timeBase)
    : _propotionalGain(1.0f), _integralGain(1.0f), _derivativeGain(1.0f), _timeBase(timeBase) {}

PID::PID(float propotionalGain, TimeSource timeBase)
    : _propotionalGain(propotionalGain), _integralGain(1.0f), _derivativeGain(1.0f), _timeBase(timeBase) {}

PID::PID(float propotionalGain, float integralGain, TimeSource timeBase)
    : _propotionalGain(propotionalGain), _integralGain(integralGain), _derivativeGain(1.0f), _timeBase(timeBase) {}

PID::PID(float propotionalGain, float integralGain, float derivativeGain, TimeSource timeBase)
    : _propotionalGain(propotionalGain), _integralGain(integralGain), _derivativeGain(derivativeGain),
      _timeBase(timeBase) {}

void PID::setIntegralTimeConstant(float timeConstant) { _integral.setTimeConstant(timeConstant); }

void PID::setDerivativeTimeConstant(float timeConstant) { _derivative.setTimeConstant(timeConstant); }

float PID::update(float error) {
  float controlSignal;

  // variables for integral term ..
  static float inputValueIt = 0.0f;
  static float outputValueIt = 0.0f;

  // variables for derivative term..
  static float inputValueDt = 0.0f;
  static float outputValueDt = 0.0f;

  // ******************* INTEGRAL TERM *********************
  inputValueIt = error * _integralGain;
  outputValueIt = integralUpdate(inputValueIt);

  // ******************* DERIVATIVE TERM *********************
  inputValueDt = error * _derivativeGain;
  outputValueDt = derivativeUpdate(inputValueDt);

  controlSignal = _propotionalGain * error + outputValueIt + outputValueDt;
  return controlSignal;
}

float PID::integralUpdate(float inputValue) { return _integral.update(inputValue); }

float PID::derivativeUpdate(float inputValue) { return _derivative.update(inputValue); }
