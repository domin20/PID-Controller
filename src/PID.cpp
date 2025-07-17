#include "PID.h"

PID::PID(ClockSource clockSource)
    : _proportionalGain(1.0f), _integralGain(1.0f), _derivativeGain(1.0f), _integral(clockSource),
      _derivative(clockSource) {}

PID::PID(float propotionalGain, ClockSource clockSource)
    : _proportionalGain(propotionalGain), _integralGain(1.0f), _derivativeGain(1.0f), _integral(clockSource),
      _derivative(clockSource) {}

PID::PID(float propotionalGain, float integralGain, ClockSource clockSource)
    : _proportionalGain(propotionalGain), _integralGain(integralGain), _derivativeGain(1.0f), _integral(clockSource),
      _derivative(clockSource) {}

PID::PID(float propotionalGain, float integralGain, float derivativeGain, ClockSource clockSource)
    : _proportionalGain(propotionalGain), _integralGain(integralGain), _derivativeGain(derivativeGain),
      _integral(clockSource), _derivative(clockSource) {}

void PID::setIntegralTimeConstant(float timeConstant) { _integral.setTimeConstant(timeConstant); }

void PID::setDerivativeTimeConstant(float timeConstant) { _derivative.setTimeConstant(timeConstant); }

float PID::update(float error) {
  // ******************* INTEGRAL TERM *********************
  _inputValueIt = error * _integralGain;
  _outputValueIt = _integral.update(_inputValueIt);

  // ******************* DERIVATIVE TERM *********************
  _inputValueDt = error * _derivativeGain;
  _outputValueDt = _derivative.update(_inputValueDt);

  float controlSignal = _proportionalGain * error + _outputValueIt + _outputValueDt;
  return controlSignal;
}
