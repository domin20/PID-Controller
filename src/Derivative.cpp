#include "Derivative.h"
#include <math.h>

Derivative::Derivative(ClockSource timeBase)
    : _timeConstant(1.0f), _rawValueDifference(0.0f), _processedValueDifference(0.0f), _outputValue(0.0f),
      _exponent(0.0f), _previousTimeStamp(0), _timeBase(timeBase) {}

Derivative::Derivative(float timeConstant, ClockSource timeBase)
    : _timeConstant(timeConstant), _rawValueDifference(0.0f), _processedValueDifference(0.0f), _outputValue(0.0f),
      _exponent(0.0f), _previousTimeStamp(0), _timeBase(timeBase) {}

float Derivative::update(float rawInputValue) {
  if (!_timeBase) {
    return 0;
  }
  _exponent = (_timeBase() - _previousTimeStamp) / (_timeConstant * 1000.0f);

  _previousTimeStamp = _timeBase();
  _difference = rawInputValue - _previousRawInputValue;
  _outputValue += _difference;

  if (_outputValue >= 0.0f) {
    _processedValueDifference = _outputValue * (1.0f - pow(_INVERSE_EULER, _exponent));
    _outputValue -= _processedValueDifference;
  } else {
    _processedValueDifference = _rawValueDifference * (1.0f - pow(_INVERSE_EULER, _exponent));
    _outputValue += _processedValueDifference;
  }
  _previousRawInputValue = rawInputValue;
  return _outputValue;
}

void Derivative::setTimeConstant(float timeConstant) { _timeConstant = timeConstant; }
