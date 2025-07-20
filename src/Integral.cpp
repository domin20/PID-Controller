#include "Integral.h"
#include <math.h>

// Should be removed and need to add RCFilter for other things
Integral::Integral() : _outputValue(0.0f), _previousTimeStamp(0), _clockSource() {}

Integral::Integral(ClockSource clockSource) : _outputValue(0.0f), _previousTimeStamp(0), _clockSource(clockSource) {}

float Integral::update(float error) {
  if (!_clockSource) {
    return 0;
  }
  float dt = (_clockSource() - _previousTimeStamp) / 1000.0f;
  _previousTimeStamp = _clockSource();

  _outputValue += error * dt;
  if (_isLimitSet) {
    if (_outputValue > _maxLimit) {
      _outputValue = _maxLimit;
    } else if (_outputValue < _minLimit) {
      _outputValue = _minLimit;
    }
  }
  return _outputValue;
}

void Integral::setClockSource(ClockSource clockSource) { _clockSource = clockSource; }

void Integral::setIntegralLimits(float min, float max) {
  _minLimit = min;
  _maxLimit = max;
  _isLimitSet = true;
}

float Integral::getOutputValue() { return _outputValue; }

void Integral::reset() { _outputValue = 0; }
