#pragma once
#include "Integral.h"

template <uint8_t OrderOfInertia>
class Inertia {
 public:
  Inertia() : _orderOfInertia(OrderOfInertia) {}
  Inertia(TimeSource timeBase) : _timeBase(timeBase), _orderOfInertia(OrderOfInertia) {}
  ~Inertia() {}

  void setTimeBase(TimeSource timeBase) { _timeBase = timeBase; }

  void setTimeConstant(float timeConstant) {
    for (auto& integral : _integralTerms) {
      integral.setTimeConstant(timeConstant);
    }
  }

  float update(float rawInputValue) {
    float inputValue = rawInputValue;
    for (auto& integral : _integralTerms) {
      inputValue = integral.update(inputValue);
    }
    return inputValue;
  }

  void reset() {
    for (auto& integral : _integralTerms) {
      integral.reset();
    }
  }

 private:
  TimeSource _timeBase;
  Integral _integralTerms[OrderOfInertia];
  const uint8_t _orderOfInertia;
};
