#include "Integral.h"
#include <math.h>

Integral::Integral(TimeSource timeBase)
    : _timeConstant(1.0f), _rawValueDifference(0.0f), _processedValueDifference(0.0f), _outputValue(0.0f),
      _exponent(0.0f), _isRising(true), _previousTimeStamp(0), _timeBase(timeBase) {}

Integral::Integral(float timeConstant, TimeSource timeBase)
    : _timeConstant(timeConstant), _rawValueDifference(0.0f), _processedValueDifference(0.0f), _outputValue(0.0f),
      _exponent(0.0f), _isRising(true), _previousTimeStamp(0), _timeBase(timeBase) {}

float Integral::update(float rawInputValue) {
  if (!_timeBase) {
    return 0;
  }
  _exponent = (_timeBase() - _previousTimeStamp) / (_timeConstant * 1000.0f);
  _previousTimeStamp = _timeBase();
  if (rawInputValue >= _outputValue) {
    _isRising = true;
  } else {
    _isRising = false;
  }

  if (_isRising) {
    _rawValueDifference = rawInputValue - _outputValue;
    _processedValueDifference = _rawValueDifference * (1.0f - pow(_INVERSE_EULER, _exponent));
    _outputValue += _processedValueDifference;
  } else {
    _rawValueDifference = _outputValue - rawInputValue;
    _processedValueDifference = _rawValueDifference * (1.0f - pow(_INVERSE_EULER, _exponent));
    _outputValue -= _processedValueDifference;
  }
  return _outputValue;
}

void Integral::setTimeConstant(float timeConstant) { _timeConstant = timeConstant; }

void Integral::reset() { _outputValue = 0; }
