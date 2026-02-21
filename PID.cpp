#include "PID.h"
#include <math.h>

PID::PID(ClockSource clockSource)
    : _clockSource(clockSource), _proportionalGain(1.0f), _integralGain(1.0f), _derivativeGain(1.0f) {}

PID::PID(float propotionalGain, ClockSource clockSource)
    : _clockSource(clockSource), _proportionalGain(propotionalGain), _integralGain(1.0f), _derivativeGain(1.0f) {}

PID::PID(float propotionalGain, float integralGain, ClockSource clockSource)
    : _clockSource(clockSource), _proportionalGain(propotionalGain), _integralGain(integralGain),
      _derivativeGain(1.0f) {}

PID::PID(float propotionalGain, float integralGain, float derivativeGain, ClockSource clockSource)
    : _clockSource(clockSource), _proportionalGain(propotionalGain), _integralGain(integralGain),
      _derivativeGain(derivativeGain) {}

void PID::setIntegralLimits(float min, float max) {
  _minIntegralLimit = min;
  _maxIntegralLimit = max;
  _isIntegralLimitSet = true;
}

void PID::setDerivativeTimeConstant(float timeConstant) { _derivativeTimeConstant = timeConstant; }

float PID::update(float error) {
  if (!_clockSource) {
    return 0;
  }

  _proportionalTermResultValue = _proportionalGain * error;

  // ******************* INTEGRAL TERM *********************
  float dt = (_clockSource() - _integralPreviousTimeStamp) / 1000.0f;
  _integralPreviousTimeStamp = _clockSource();

  _integralOutputValue += error * dt;
  if (_isIntegralLimitSet) {
    if (_integralOutputValue > _maxIntegralLimit) {
      _integralOutputValue = _maxIntegralLimit;
    } else if (_integralOutputValue < _minIntegralLimit) {
      _integralOutputValue = _minIntegralLimit;
    }
  }
  _integralTermResultValue = _integralGain * _integralOutputValue;
  // *********************************************************

  // ******************* DERIVATIVE TERM *********************
  if (_derivativePreviousTimeStamp == 0) {
    _derivativePreviousTimeStamp = _clockSource();
    _derivativePreviousError = error;
    return 0.0f;
  }

  uint64_t currentTime = _clockSource();
  float deltaTime = (currentTime - _derivativePreviousTimeStamp) / 1000.0f;
  _derivativePreviousTimeStamp = currentTime;

  if (deltaTime <= 0.0f) {
    return _derivativeOutputValue;
  }

  float derivative = (error - _derivativePreviousError) / deltaTime;
  _derivativePreviousError = error;

  // Wygładzanie wykładnicze (filtr LPF)
  float alpha = 1.0f - expf(-deltaTime / _derivativeTimeConstant);
  _derivativeOutputValue += alpha * (derivative - _derivativeOutputValue);
  _derivativeTermResultValue = _derivativeGain * _derivativeOutputValue;
  // *********************************************************

  float controlSignal = _proportionalTermResultValue + _integralTermResultValue + _derivativeTermResultValue;
  return controlSignal;
}
