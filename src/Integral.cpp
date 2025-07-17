#include "Integral.h"
#include <math.h>

Integral::Integral()
    : _timeConstant(1.0f), _processedValueDifference(0.0f), _outputValue(0.0f), _exponent(0.0f), _previousTimeStamp(0),
      _clockSource() {}

Integral::Integral(ClockSource clockSource)
    : _timeConstant(1.0f), _processedValueDifference(0.0f), _outputValue(0.0f), _exponent(0.0f), _previousTimeStamp(0),
      _clockSource(clockSource) {}

Integral::Integral(float timeConstant, ClockSource clockSource)
    : _timeConstant(timeConstant), _processedValueDifference(0.0f), _outputValue(0.0f), _exponent(0.0f),
      _previousTimeStamp(0), _clockSource(clockSource) {}

float Integral::update(float rawInputValue) {
  if (!_clockSource) {
    return 0;
  }
  _exponent = (_clockSource() - _previousTimeStamp) / (_timeConstant * 1000.0f);
  _previousTimeStamp = _clockSource();

  _processedValueDifference = (rawInputValue - _outputValue) * (1.0f - pow(INVERSE_EULER, _exponent));
  _outputValue += _processedValueDifference;
  return _outputValue;
}

void Integral::setClockSource(ClockSource clockSource) { _clockSource = clockSource; }

void Integral::setTimeConstant(float timeConstant) { _timeConstant = timeConstant; }

void Integral::reset() { _outputValue = 0; }
