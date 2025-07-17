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

void PID::setDerivativeTimeConstant(float timeConstant) { _derivative.setTimeConstant(timeConstant); }

float PID::update(float error) {
  _proportionalTermValue = _proportionalGain * error;

  // ******************* INTEGRAL TERM *********************
  _integralTermValue = _integralGain * _integral.update(error);

  // ******************* DERIVATIVE TERM *********************
  _derivativeTermValue = _derivativeGain * _derivative.update(error);

  float controlSignal = _proportionalTermValue + _integralTermValue + _derivativeTermValue;
  return controlSignal;
}
