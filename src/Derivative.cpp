#include "Derivative.h"
#include <math.h>

Derivative::Derivative(ClockSource clockSource)
    : _timeConstant(1.0f), _outputValue(0.0f), _previousTimeStamp(0), _clockSource(clockSource) {}

Derivative::Derivative(float timeConstant, ClockSource clockSource)
    : _timeConstant(timeConstant), _outputValue(0.0f), _previousTimeStamp(0), _clockSource(clockSource) {}

float Derivative::update(float rawInputValue) {
  if (_previousTimeStamp == 0) {
    _previousTimeStamp = _clockSource();
    _previousInput = rawInputValue;
    return 0.0f;
  }

  uint64_t currentTime = _clockSource();
  float deltaTime = (currentTime - _previousTimeStamp) / 1000.0f;
  _previousTimeStamp = currentTime;

  if (deltaTime <= 0.0f) {
    return _outputValue;
  }

  float derivative = (rawInputValue - _previousInput) / deltaTime;
  _previousInput = rawInputValue;

  // Wygładzanie wykładnicze (filtr LPF)
  float alpha = 1.0f - expf(-deltaTime / _timeConstant);
  _outputValue += alpha * (derivative - _outputValue);

  return _outputValue;
}

void Derivative::setTimeConstant(float timeConstant) { _timeConstant = timeConstant; }