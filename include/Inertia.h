#pragma once
#include "Integral.h"

template <uint8_t OrderOfInertia>
class Inertia {
 public:
  Inertia(ClockSource clockSource) : _clockSource(clockSource), _orderOfInertia(OrderOfInertia) {}

  void init() {
    for (auto& integral : _integralTerms) {
      integral.setClockSource(_clockSource);
    }
  }

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
  ClockSource _clockSource;
  Integral _integralTerms[OrderOfInertia];
  const uint8_t _orderOfInertia;
};
