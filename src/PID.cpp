#include "PID.h"

#include <math.h>

PID::PID(TimeSource timeBase)
    : _propotionalGain(1.0f), _integralGain(1.0f), _derivativeGain(1.0f), _timeBase(timeBase) {}

PID::PID(float propotionalGain, TimeSource timeBase)
    : _propotionalGain(propotionalGain), _integralGain(1.0f), _derivativeGain(1.0f), _timeBase(timeBase) {}

PID::PID(float propotionalGain, float integralGain, TimeSource timeBase)
    : _propotionalGain(propotionalGain), _integralGain(integralGain), _derivativeGain(1.0f), _timeBase(timeBase) {}

PID::PID(float propotionalGain, float integralGain, float derivativeGain, TimeSource timeBase)
    : _propotionalGain(propotionalGain), _integralGain(integralGain), _derivativeGain(derivativeGain),
      _timeBase(timeBase) {}

void PID::pidInit(float propotionalGain, float integralGain, float derivativeGain) {
  _propotionalGain = propotionalGain;
  _integralGain = integralGain;
  _derivativeGain = derivativeGain;
}

void PID::setIntegralTimeConstant(float timeConstant) { _integral.setTimeConstant(timeConstant); }

void PID::setDerivativeTimeConstant(float timeConstant) { _derivative.setTimeConstant(timeConstant); }

float PID::pidUpdate(float error) {
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

Integral::Integral()
    : _timeConstant(1.0f), _rawValueDifference(0.0f), _processedValueDifference(0.0f), _outputValue(0.0f),
      _exponent(0.0f), _isRising(true), _previousTimeStamp(0), _timeBase() {}

Integral::Integral(TimeSource timeBase)
    : _timeConstant(1.0f), _rawValueDifference(0.0f), _processedValueDifference(0.0f), _outputValue(0.0f),
      _exponent(0.0f), _isRising(true), _previousTimeStamp(0), _timeBase(timeBase) {}

Integral::Integral(float timeConstant, TimeSource timeBase)
    : _timeConstant(timeConstant), _rawValueDifference(0.0f), _processedValueDifference(0.0f), _outputValue(0.0f),
      _exponent(0.0f), _isRising(true), _previousTimeStamp(0), _timeBase(timeBase) {}

void Integral::setTimeBase(TimeSource timeBase) { _timeBase = timeBase; }

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

Derivative::Derivative()
    : _timeConstant(1.0f), _rawValueDifference(0.0f), _processedValueDifference(0.0f), _outputValue(0.0f),
      _exponent(0.0f), _previousTimeStamp(0), _timeBase() {}

Derivative::Derivative(TimeSource timeBase)
    : _timeConstant(1.0f), _rawValueDifference(0.0f), _processedValueDifference(0.0f), _outputValue(0.0f),
      _exponent(0.0f), _previousTimeStamp(0), _timeBase(timeBase) {}

Derivative::Derivative(float timeConstant, TimeSource timeBase)
    : _timeConstant(timeConstant), _rawValueDifference(0.0f), _processedValueDifference(0.0f), _outputValue(0.0f),
      _exponent(0.0f), _previousTimeStamp(0), _timeBase(timeBase) {}

void Derivative::setTimeBase(TimeSource timeBase) { _timeBase = timeBase; }

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
