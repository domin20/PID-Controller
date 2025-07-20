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

void PID::setIntegralLimits(float min, float max) { _integral.setIntegralLimits(min, max); }

void PID::setDerivativeTimeConstant(float timeConstant) { _derivative.setTimeConstant(timeConstant); }

float PID::update(float error) {
  _proportionalTermResultValue = _proportionalGain * error;

  // ******************* INTEGRAL TERM *********************
  _integralTermResultValue = _integralGain * _integral.update(error);

  // ******************* DERIVATIVE TERM *********************
  _derivativeTermResultValue = _derivativeGain * _derivative.update(error);

  float controlSignal = _proportionalTermResultValue + _integralTermResultValue + _derivativeTermResultValue;
  return controlSignal;
}
