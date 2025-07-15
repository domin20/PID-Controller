#pragma once

#include <memory>
#include <vector>
#include "Config.h"

class Integral {
 public:
  explicit Integral();
  explicit Integral(TimeSource timeBase);
  explicit Integral(float timeConstant, TimeSource timeBase);

  void setTimeBase(TimeSource timeBase);

  float update(float rawInputValue);
  void setTimeConstant(float timeConstant);
  void reset();

 private:
  float _timeConstant;
  float _rawValueDifference;
  float _processedValueDifference;
  float _outputValue;
  float _exponent;

  bool _isRising;
  uint64_t _previousTimeStamp;

  TimeSource _timeBase;
  static constexpr float _INVERSE_EULER = 0.368f; // inverse euler
};

class Derivative {
 public:
  explicit Derivative();
  explicit Derivative(TimeSource timeBase);
  explicit Derivative(float timeConstant, TimeSource timeBase);

  void setTimeBase(TimeSource timeBase);

  float update(float rawInputValue);
  void setTimeConstant(float timeConstant);

 private:
  float _timeConstant;
  static const float _INVERSE_EULER; // inverse euler
  float _rawValueDifference;
  float _processedValueDifference;
  float _previousRawInputValue;
  float _outputValue;
  float _exponent;
  float _difference;

  uint64_t _previousTimeStamp;

  TimeSource _timeBase;
};

class Inertia {
 public:
  Inertia() {}
  Inertia(TimeSource timeBase) : _timeBase(timeBase) {}
  ~Inertia() {}

  void setTimeBase(TimeSource timeBase);
  void setTimeConstant(float timeConstant);
  void setOrderOfInertia(uint8_t orderOfInertia);
  float update(float rawInputValue);
  void reset();

 private:
  TimeSource _timeBase;
  std::vector<Integral> _integralTerms;
};

class PID {
 public:
  explicit PID(TimeSource timeBase);
  explicit PID(float propotionalGain, TimeSource timeBase);
  PID(float propotionalGain, float integralGain, TimeSource timeBase);
  PID(float propotionalGain, float integralGain, float derivativeGain, TimeSource timeBase);
  ~PID() {};

  void setIntegralTimeConstant(float timeConstant);
  void setDerivativeTimeConstant(float timeConstant);
  void pidInit(float propotionalGain, float integralGain, float derivativeGain);

  float pidUpdate(float error);

 private:
  float integralUpdate(float inuptValue);
  float derivativeUpdate(float inputValue);

 private:
  float _propotionalGain;
  float _integralGain;
  float _derivativeGain;

  TimeSource _timeBase;
  Integral _integral = Integral(_timeBase);
  Derivative _derivative = Derivative(_timeBase);
};
